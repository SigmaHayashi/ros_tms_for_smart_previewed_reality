#!/usr/bin/env python
# -*- coding: utf-8 -*- 
import rospy
import genpy
import pymongo # https://api.mongodb.org/python/2.6.3/
import json
import copy
from bson import json_util
from bson.objectid import ObjectId
from datetime import *
from tms_msg_db.msg import TmsdbStamped, Tmsdb
import tms_db_manager.tms_db_util as db_util

client = pymongo.MongoClient('localhost:27017')
db = client.rostmsdb

class TmsDbReplayer():
    def __init__(self):
        rospy.init_node("tms_db_replayer")
        rospy.on_shutdown(self.shutdown)

        db_host = 'localhost'
        db_port = 27017
        self.is_connected = db_util.check_connection(db_host, db_port)
        if not self.is_connected:
            raise Exception("Problem of connection")

        self.sendDbHistoryInformation(range(1006, 1019), 'tms_db_replayer', '2016-01-18T04:00:00', '2016-01-18T05:00:00', 600)

    def sendDbHistoryInformation(self, id_array, topic_name, start_date, end_date, play_speed):
        # Input
        d1 = datetime.strptime(start_date, '%Y-%m-%dT%H:%M:%S')
        d2 = datetime.strptime(end_date, '%Y-%m-%dT%H:%M:%S')
        t1 = 'ISODate('+d1.isoformat()+')'
        t2 = 'ISODate('+d2.isoformat()+')'

        self.data_pub = rospy.Publisher(topic_name, TmsdbStamped, queue_size=10)

        # Extract data from DB
        temp_dbdata = Tmsdb()
        object_information = TmsdbStamped()
        rospy.loginfo('Extracting data: from {0} to {1}'.format(t1,t2))
        db.history.create_index([('time', pymongo.ASCENDING), ('id', pymongo.ASCENDING)])

        # Publish data
        rate = rospy.Rate(100)  # [Hz] : Keep consistence with db_publisher
        rospy.loginfo('Start to publish data.')
        prev_time = d1
        t_delta = timedelta(milliseconds=10*play_speed)
        curr_time = d1 + t_delta
        while rospy.is_shutdown() or curr_time <= d2:
            t1 = 'ISODate('+prev_time.isoformat()+')'
            t2 = 'ISODate('+curr_time.isoformat()+')'
            rospy.loginfo('from {0} to {1}'.format(t1,t2))

            cursor = db.history.find({'$or':[json.loads('{"id":'+str(x)+'}') for x in id_array], 'time':{'$gte':t1,'$lt':t2}, 'state':1})
            for doc in cursor:
                del doc['_id']
                temp_dbdata = db_util.document_to_msg(doc, Tmsdb)
                object_information.tmsdb.append(temp_dbdata)
            self.data_pub.publish(object_information)
            prev_time = curr_time
            curr_time += t_delta
            rate.sleep()

        rospy.loginfo('Finish publishing data.')

    def shutdown(self):
        rospy.loginfo("Stopping the node")

if __name__ == '__main__':
    try:
        TmsDbReplayer()
    except rospy.ROSInterruptException:
        rospy.loginfo("tms_db_replayer node terminated.")
#!/usr/bin/env python
# -*- coding:utf-8 -*-

# ROS dependency
import rospy
from tms_msg_ss.msg import Skeleton, SkeletonArray
from geometry_msgs.msg import Vector3, Quaternion

JOINT_NAME = (
    'SpineBase',
    'SpineMid',
    'Neck',
    'Head',
    'ShoulderLeft',
    'ElbowLeft',
    'WristLeft',
    'HandLeft',
    'ShoulderRight',
    'ElbowRight',
    'WristRight',
    'HandRight',
    'HipLeft',
    'KneeLeft',
    'AnkleLeft',
    'FootLeft',
    'HipRight',
    'KneeRight',
    'AnkleRight',
    'FootRight',
    'SpineShoulder',
    'HandTipLeft',
    'ThumbLeft',
    'HandTipRight',
    'ThumbRight'
    )

# -----------------------------------------------------------------------------
INPUT_JOINT_DATA = ((
    (0.0, 0.0, 0.0),
    (0.0, 0.0, 1.1),
    (0.0, 0.0, 1.45),
    (0.0, 0.04, 1.48),
    (-0.185, 0.0, 1.39),
    (-0.4, 0.0, 1.39),
    (-0.62, 0.0, 1.39),
    (0.0, 0.0, 0.0),
    (0.185, 0.0, 1.39),
    (0.4, 0.0, 1.39),
    (0.62, 0.0, 1.39),
    (0.0, 0.0, 0.0),
    (-0.072, 0.0, 0.85),
    (-0.072, 0.0, 0.55),
    (-0.072, 0.0, 0.13),
    (0.0, 0.0, 0.0),
    (0.072, 0.0, 0.85),
    (0.072, 0.0, 0.55),
    (0.072, 0.0, 0.13),
    (0.0, 0.0, 0.0),
    (0.0, 0.0, 0.0),
    (0.0, 0.0, 0.0),
    (0.0, 0.0, 0.0),
    (0.0, 0.0, 0.0),
    (0.0, 0.0, 0.0)
    ),)

# -----------------------------------------------------------------------------
if __name__ == '__main__':
    try:
        pub_test_skeleton = rospy.Publisher('integrated_skeleton_stream',
                                            SkeletonArray, queue_size=1)
        test_skeleton_data = SkeletonArray()

        # Initialization
        test_skeleton_data.data = []

        # Set data
        user_count = 0
        loop_list = zip(INPUT_JOINT_DATA, range(1, len(INPUT_JOINT_DATA)+1))
        for it in loop_list:
            joints, user_count = it

            test_skeleton = Skeleton()
            test_skeleton.user_id = user_count
            loop_list2 = zip(joints, JOINT_NAME)
            for it2 in loop_list2:
                joint, joint_name = it2

                joint_position = Vector3()
                joint_position.x = joint[0] + 2*(user_count-1)
                joint_position.y = joint[1] + 2*(user_count-1)
                joint_position.z = joint[2]
                joint_orientation = Quaternion()
                joint_orientation.x = 0.0
                joint_orientation.y = 0.0
                joint_orientation.z = 0.0
                joint_orientation.w = 1.0

                test_skeleton.name.append(joint_name)
                test_skeleton.confidence.append(2.0)
                test_skeleton.position.append(joint_position)
                test_skeleton.orientation.append(joint_orientation)

            test_skeleton_data.data.append(test_skeleton)

        rospy.init_node('test_skeleton_stream')

        r = rospy.Rate(10)
        while not rospy.is_shutdown():
            rospy.loginfo("Published skeleton array for testing")
            pub_test_skeleton.publish(test_skeleton_data)
            r.sleep()

    except rospy.ROSInterruptException:
        pass

<<<<<<< HEAD
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <vector>
#include <string.h>
#include <pthread.h>
=======
// ParticleFilter.cpp : Àt@C
//
  #include <stdio.h>
  #include <stdlib.h>
  #include <math.h>
  #include <vector>
  #include <string.h>
  #include <pthread.h>
>>>>>>> 51ecc3540900cfe208d8c2ca1ecaf2184d407ca7

//#include "opencv2/opencv.hpp"
#include <opencv/cv.h>
#include <opencv/highgui.h>

#include "define.h"
#include "target.h"
#include "laser.h"
#include "particle_filter.h"

#include "multiple_particle_filter.h"

<<<<<<< HEAD
extern pthread_mutex_t mutex_laser;
extern pthread_mutex_t mutex_target;

CMultipleParticleFilter::CMultipleParticleFilter()
{
  m_max_ID = Config::is()->m_max_ID;
  m_min_distance = Config::is()->m_min_distance;  // 1mä»¥ä¸é¢ãã¦åºç¾ããã¨ãã ããæ°ããPFãçæ
  m_initial_dist = Config::is()->m_initial_dist;  // 0.5måæ¹ã«ãã¼ãã£ã¯ã«ãåæéç½®
  m_max_lost_count = 1;  // ä½åé£ç¶ã§ãã¼ã¿ãå¾ãããªãã£ãã
  Area[0] = Config::is()->target_area[0];
  Area[1] = Config::is()->target_area[1];
  Area[2] = Config::is()->target_area[2];
  Area[3] = Config::is()->target_area[3];

  m_ID = 0;
=======
  extern pthread_mutex_t mutex_laser;
  extern pthread_mutex_t mutex_target;

CMultipleParticleFilter::CMultipleParticleFilter()
{
	m_max_ID = Config::is()->m_max_ID;
	m_min_distance = Config::is()->m_min_distance;	// 1000mmÈã£êÄo»µ½Æ«¾¯AVµ¢PFð¶¬
	m_initial_dist = Config::is()->m_initial_dist;	// 500mmlûÉp[eBNðúzu

	m_ID = 0;
>>>>>>> 51ecc3540900cfe208d8c2ca1ecaf2184d407ca7
}

CMultipleParticleFilter::~CMultipleParticleFilter()
{
<<<<<<< HEAD
  m_ParticleFilter.clear();
=======
	m_ParticleFilter.clear();
>>>>>>> 51ecc3540900cfe208d8c2ca1ecaf2184d407ca7
}

void CMultipleParticleFilter::update(CLaser *Laser)
{
<<<<<<< HEAD
  m_pLaser = Laser;
  double obs[2], p[2];

  // å¤±æ¢ç¥ããåæ°ã®ã«ã¦ã³ã¿ãå¢ãã ããï¼ä»¥ä¸ã§ãã¼ãã£ã¯ã«ãã£ã«ã¿ãæ´æ°ï¼çæããããï¼0ã«ãªã»ããããã
  for (vector< CPF >::iterator it = m_ParticleFilter.begin(); it != m_ParticleFilter.end(); ++it)
  {
    it->IncLostCnt();
  }

  for (int n = 0; n < m_pLaser->m_cnMaxConnect; n++)
  {
    if (m_pLaser->m_bNodeActive[n])
    {
      std::vector< int > label(m_pLaser->m_LRFClsPoints[n].size(), -1);  // ã¯ã©ã¹ã¿ã«å¯¾å¿ãããã¼ãã£ã¯ã«ãã£ã«ã¿ã®çªå·
      int pn = m_ParticleFilter.size();                                  // ç¾å¨ã®ãã¼ãã£ã¯ã«ãã£ã«ã¿ã®åæ°

      for (int j = 0; j < m_pLaser->m_LRFClsPoints[n].size(); j++)
      {
        // ã¯ã©ã¹ã¿ä»£è¡¨ç¹
        obs[0] = m_pLaser->m_LRFClsPoints[n][j].x;
        obs[1] = m_pLaser->m_LRFClsPoints[n][j].y;

        // ã¯ã©ã¹ã¿æ¯ã«ï¼ä¸çªè¿ããã¼ãã£ã¯ã«ãã£ã«ã¿ãæ¢ã
        double min_r = 1e10;
        int min_np = -1;
        int np = 0;
        for (vector< CPF >::iterator it = m_ParticleFilter.begin(); it != m_ParticleFilter.end(); ++it, ++np)
        {
          p[0] = it->state[0];
          p[1] = it->state[1];

          double r = sqrt(pow(p[0] - obs[0], 2) + pow(p[1] - obs[1], 2));
          // ã¯ã©ã¹ã¿ã¨æ¢å­ã®ãã¼ãã£ã¯ã«ãã£ã«ã¿ã¨ã®è·é¢ãm_min_distanceä»¥ä¸ãªãï¼æ¢å­ã®ãã¼ãã£ã¯ã«ãã£ã«ã¿ã«ç´ã¥ã
          if (r < m_min_distance)
          {
            if (min_r > r) {
               min_r = r;
               min_np = np;
            }
          }
        }

        // ããï¼ã¯ã©ã¹ã¿ã«å¯¾å¿ãããã¼ãã£ã¯ã«ãã£ã«ã¿ããªãã£ãã¨ã
        if (min_r < m_min_distance) {
          label[j] = min_np; // å¯¾å¿ãããã¼ãã£ã¯ã«ãã£ã«ã¿ã®çªå·ãä¿å­
        } else {
          label[j] = pn++; // æ°ãã«ãã¼ãã£ã¯ã«ãã£ã«ã¿ãçæããããã«ï¼æ°è¦ã®çªå·ãä¸ãã
        }

      }

      for (int j = 0; j < m_pLaser->m_LRFClsPoints[n].size(); j++)
      {
        if (label[j] < 0)
        {
          std::cout << "Error" << std::endl;
        }
        else if (label[j] < m_ParticleFilter.size())
        {
          // æ¢å­ã®ãã¼ãã£ã¯ã«ãã£ã«ã¿ãæ´æ°
          obs[0] = m_pLaser->m_LRFClsPoints[n][j].x;
          obs[1] = m_pLaser->m_LRFClsPoints[n][j].y;
          m_ParticleFilter[label[j]].SetTarget(obs);
          m_ParticleFilter[label[j]].update();
        }
        else
        {
          // æ°ãã«ãã¼ãã£ã¯ã«ãã£ã«ã¿ãçæ
          CPF pf;
          //int d = Config::is()->particle_area;
          obs[0] = m_pLaser->m_LRFClsPoints[n][j].x;
          obs[1] = m_pLaser->m_LRFClsPoints[n][j].y;
          if ((obs[0] < Area[0]) || (obs[0] >= Area[2]) || (obs[1] < Area[1]) || (obs[1] >= Area[3])) continue;

          int area[4] = {obs[0] - m_initial_dist / 2, obs[1] - m_initial_dist / 2, obs[0] + m_initial_dist / 2,
                         obs[1] + m_initial_dist / 2};
          pf.initialize(area);

          pf.SetTarget(obs);
          pf.SetID(m_ID++);
          pf.update();
          if(!isnan(pf.state[0]) && !isnan(pf.state[1]))
          m_ParticleFilter.push_back(pf);

        }
      }
    }
  }

  for (vector< CPF >::iterator it = m_ParticleFilter.begin(); it != m_ParticleFilter.end(); ++it)
  {
    // å¤æ°åï¼æ´æ°ãçæãããã¦ããªããã¼ãã£ã¯ã«ãã£ã«ã¿ãæ¶å»
    if (it->GetLostCnt() >= m_max_lost_count)
    {
      it->clear();
      it = m_ParticleFilter.erase(it);
      if (it == m_ParticleFilter.end())
        break;
    }
  }

  // è¿½è·¡çµæï¼m_pTargetï¼ã®æå ±ãæ´æ°
  for (int i = 0; i < MAX_TRACKING_OBJECT; i++)
  {
    delete m_pLaser->m_pTarget[i];
    m_pLaser->m_pTarget[i] = NULL;
  }

  int np = 0;
  for (vector< CPF >::iterator it = m_ParticleFilter.begin(); it != m_ParticleFilter.end(); ++it, ++np)
  {
    if(np >= MAX_TRACKING_OBJECT) break;
    m_pLaser->m_pTarget[np] = new CTarget();
    m_pLaser->m_pTarget[np]->id = it->GetID();
    m_pLaser->m_pTarget[np]->cnt = it->GetCnt();
    m_pLaser->m_pTarget[np]->SetPosi(it->state[0], it->state[1]);
  }

  std::cout << "Total number of particle filters " << m_ParticleFilter.size() << std::endl;

=======
	m_pLaser = Laser;
	double obs[2], p[2];

	for (int n = 0; n < 1; n++){
		if (m_pLaser->m_bNodeActive[n]){
			std::vector<int> label(m_pLaser->m_LRFClsPoints[n].size(), -1);		// NX^ÉÎ·ép[eBNtB^ÌÔ
			int pn = m_ParticleFilter.size();	// »ÝÌp[eBNtB^ÌÂ

			for (int j = 0; j < m_pLaser->m_LRFClsPoints[n].size(); j++){
				// NX^ã\_
				obs[0] = m_pLaser->m_LRFClsPoints[n][j].x;
				obs[1] = m_pLaser->m_LRFClsPoints[n][j].y;

				// NX^ÉCêÔß¢p[eBNtB^ðT·
				double min_r = 1e10;
				int np = 0;
				for (vector<CPF>::iterator it = m_ParticleFilter.begin(); it != m_ParticleFilter.end(); ++it, ++np) {
					p[0] = it->state[0];
					p[1] = it->state[1];

					double r = sqrt(pow(p[0] - obs[0], 2) + pow(p[1] - obs[1], 2));

					if (min_r > r && r < m_min_distance){
						min_r = r;
						label[j] = np;
					}
				}

				// àµCNX^ÉÎ·ép[eBNtB^ªÈ©Á½Æ«
				if (min_r >= m_min_distance){
					label[j] = pn++;
				}
			}

			std::vector<int> flg(pn, -1);		// NX^ÉÎ·ép[eBNtB^ÌÔ
			for (int j = 0; j < m_pLaser->m_LRFClsPoints[n].size(); j++){
				if (label[j] < 0){
					std::cout << "Error" << std::endl;
				}
				else if (label[j] < m_ParticleFilter.size()){
					obs[0] = m_pLaser->m_LRFClsPoints[n][j].x;
					obs[1] = m_pLaser->m_LRFClsPoints[n][j].y;
					m_ParticleFilter[label[j]].SetTarget(obs);
					m_ParticleFilter[label[j]].update();
				}
				else{
					CPF pf;
					int d = Config::is()->particle_area * 1000;
					obs[0] = m_pLaser->m_LRFClsPoints[n][j].x;
					obs[1] = m_pLaser->m_LRFClsPoints[n][j].y;

					int area[4] = {obs[0]-m_initial_dist/2, obs[1]-m_initial_dist/2, obs[0]+m_initial_dist/2, obs[1]+m_initial_dist/2};
					pf.initialize(area);

					pf.SetTarget(obs);
					pf.SetID(m_ID++);
					pf.update();
					m_ParticleFilter.push_back(pf);
				}
				flg[label[j]] = 1;
			}

			int np = 0;
			for (vector<CPF>::iterator it = m_ParticleFilter.begin(); it != m_ParticleFilter.end(); ++it, ++np) {
				if (flg[np] < 0)  {
					it->clear();
					it = m_ParticleFilter.erase(it);
					if (it == m_ParticleFilter.end()) break;
				}
			}

			for (int i = 0; i < MAX_TRACKING_OBJECT; i++){
				delete m_pLaser->m_pTarget[i];
				m_pLaser->m_pTarget[i] = NULL;
			}

			np = 0;
			for (vector<CPF>::iterator it = m_ParticleFilter.begin(); it != m_ParticleFilter.end(); ++it, ++np) {
				m_pLaser->m_pTarget[np] = new CTarget();
				m_pLaser->m_pTarget[np]->id = it->GetID();
				m_pLaser->m_pTarget[np]->cnt = it->GetCnt();
				m_pLaser->m_pTarget[np]->SetPosi(it->state[0], it->state[1]);
			}
		}
	}
>>>>>>> 51ecc3540900cfe208d8c2ca1ecaf2184d407ca7
}

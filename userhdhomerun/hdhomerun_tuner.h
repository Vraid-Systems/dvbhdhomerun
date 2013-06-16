/*
 * dvb_hdhomerun_tuner.h, skeleton driver for the HDHomeRun devices
 *
 * Copyright (C) 2010 Villy Thomsen <tfylliv@gmail.com>
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 2
 * of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.
 *
 */

#ifndef _hdhomerun_tuner_h_
#define _hdhomerun_tuner_h_

#include "thread_pthread.h"

#include <hdhomerun.h>

#include <string>
#include <vector>
#include <iostream>

class HdhomerunTuner : public ThreadPthread
{
public:
   enum Type
      {
         NOT_SET,
         DVBC,
         DVBT,
         ATSC
      };

public:
   HdhomerunTuner(uint32_t _device_id, uint32_t _device_ip, unsigned int _tuner, struct hdhomerun_debug_t* _dbg);
   ~HdhomerunTuner();

   void run();

   int Tune(int _freq);

   int ReadStatus();

   int ReadSignalStrength();

   int SetPesFilter(int _pid, int _output, int _pes_type);

   void StartStreaming(int _pid);
   void StopStreaming(int _pid);

   const std::string& GetName();

   void SetDataDeviceName(const std::string& _name);

   void SetKernelId(int _id) {
      m_kernelId = _id;
   }
   int GetKernelId() {
      return m_kernelId;
   }

   bool GetUseFullName() {
      return m_useFullName;
   }

   bool IsDisabled() {
      return m_isDisabled;
   }

   Type GetType() {
      return m_type;
   }

private:
   void AddPidToFilter(int _pid);
   void RemovePidFromFilter(int _pid);
   std::string GetStrFromPidFilter();

   void LogNetworkStat() const;

private:
   struct hdhomerun_device_t* m_device;
   struct hdhomerun_debug_t* m_dbg;
   bool m_stream;

   std::string m_pes_filter;

   std::vector<int> m_pidFilters;

   int m_prevFreq;

   uint32_t m_deviceId;
   uint32_t m_deviceIP;
   unsigned int m_tuner;

   int m_kernelId;

   bool m_useFullName;
   bool m_isDisabled;

   Type m_type;

   // Name returned from hdhomerun lib
   std::string m_name;

   // /dev/hdhomerun_dataX device
   std::string m_nameDataDevice;

   // For network statistic. Is UDP packets dropped?
   struct hdhomerun_video_stats_t m_stats_old;
   struct hdhomerun_video_stats_t m_stats_cur;
};

bool CompareHdhomerunTuner(HdhomerunTuner* _tuner1, HdhomerunTuner* _tuner2);

#endif // _hdhomerun_tuner_h_

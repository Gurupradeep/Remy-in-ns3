/* -*- Mode:C++; c-file-style:"gnu"; indent-tabs-mode:nil; -*- */
/*
 * Copyright (c) 2015, National Institute of Technology, Karnataka. 
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation;
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 *
 * Authors:  Guru Pradeep Reddy <gurupradeept@gmail.com>,
 *           Vaibhavi Pai <paivaibhavi15@gmail.com>,
 *           Shiv Shankar <sshivshankar@icloud.com>
 */

#ifndef TCPRATIONAL_H
#define TCPRATIONAL_H

#include "ns3/tcp-congestion-ops.h"

namespace ns3 {

class TcpRational : public TcpNewReno
{
public:
  /**
   * \brief Get the type ID.
   * \return the object TypeId
   */
  static TypeId GetTypeId (void);

  /**
   * Create an unbound tcp socket.
   */
  TcpRational (void);

  /**
   * \brief Copy constructor
   * \param sock the object to copy
   */
  TcpRational (const TcpVegas& sock);
  virtual ~TcpRational (void);

  virtual std::string GetName () const;

  virtual void PktsAcked (Ptr<TcpSocketState> tcb, uint32_t segmentsAcked,
                          const Time& rtt);

  virtual void IncreaseWindow (Ptr<TcpSocketState> tcb, uint32_t segmentsAcked);

  virtual uint32_t GetSsThresh (Ptr<const TcpSocketState> tcb,
                                uint32_t bytesInFlight);


  virtual Ptr<TcpCongestionOps> Fork ();
  virtual UpdateCongestionWindowAndPacing(void);
  virtual double InitialWindow()
//virtual void UpdateMemory(const RemyPacket packet);




}
}
/* -*- Mode:C++; c-file-style:"gnu"; indent-tabs-mode:nil; -*- */
/*
 * Copyright (c) 2017, National Institute of Technology, Karnataka. 
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

#include "tcp-rational.h"
#include "ns3/log.h"
#include "ns3/simulator.h"

namespace ns3 {

NS_LOG_COMPONENT_DEFINE ("TcpRational");
NS_OBJECT_ENSURE_REGISTERED (TcpRational);

TypeId
TcpRational::GetTypeId (void)
{
  static TypeId tid = TypeId ("ns3::TcpRational")
    .SetParent<TcpNewReno> ()
    .AddConstructor<TcpRational> ()
    .SetGroupName ("Internet")
   	//Attributes to be added
  ;
  return tid;
}

TcpRational::TcpRational (void)
  : TcpNewReno (),
  	m_intersendTime( 0.0 ),
  	m_lastsendTime( 0.0 ),
  	m_countBytesAcked( 0 )

   
{
  NS_LOG_FUNCTION (this);
}

TcpRational::TcpRational (const TcpRational& sock)
  : TcpNewReno (sock),
    m_intersendTime(sock.m_intersendTime),
  	m_lastsendTime(sock.m_lastsendTime),
  	m_countBytesAcked(sock.m_countBytesAcked)

{
  NS_LOG_FUNCTION (this);
}

TcpRational::~TcpRational
 (void)
{
  NS_LOG_FUNCTION (this);
}

Ptr<TcpCongestionOps>
TcpRational::Fork (void)
{
  return CopyObject<TcpRational> (this);
}

void
TcpRational::PktsAcked (Ptr<TcpSocketState> tcb, uint32_t segmentsAcked,
                     const Time& rtt)
{
  NS_LOG_FUNCTION (this << tcb << segmentsAcked << rtt);
  Time current_time = Simulator::Now();
  double now = current_time.GetDouble();
  double last_rtt = rtt.GetDouble();
  double g = 1/8;
  double h = 1/4;
  double delta;
  uint32_t ackcount,i;

  double last_ack_time = now;

  //Add acknowledgments part

  uint32_t timestep = 1000;
  // UpdateMemory(timestep*tcb->m_rcvTimestampEchoReply, timestep*now);
  // UpdateCongestionWindowAndPacing();

  // Acknowledgement part to be added

}
/*
void 
RationalTcpAgent::UpdateMemory( const RemyPacket packet )
{
	std::vector< RemyPacket > packets( 1, packet );
	_memory.packets_received( packets );
}

*/
void 
TcpRational :: UpdateCongestionWindowAndPacing( void )
{
	return ;
}
std::string
TcpRational::GetName () const
{
  return "TcpRational";
}


}

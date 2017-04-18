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
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <assert.h>

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
  ;
  return tid;
}


TcpRational::TcpRational (void)
  : TcpNewReno (),
  	m_intersendTime( 0.0 ),
  	m_lastsendTime( 0.0 )
{
  NS_LOG_FUNCTION (this);
}

TcpRational::TcpRational (const TcpRational& sock)
  : TcpNewReno (sock),
    m_intersendTime(sock.m_intersendTime),
  	m_lastsendTime(sock.m_lastsendTime)

{
  NS_LOG_FUNCTION (this);
}

TcpRational::~TcpRational (void)
{
  	if ( _whiskers ) {
			delete _whiskers;
		}
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
  uint32_t timestep = 1000;
  UpdateMemory(RemyPacket((unsigned int) timestep*tcb->m_rcvTimestampEchoReply, (unsigned int)timestep*now));
  IncreaseWindow(tcb,1);

}
void
TcpRational::UpdateMemory( const RemyPacket packet )
{
	std::vector< RemyPacket > packets( 1, packet );
	_memory.packets_received( packets );
}
void
TcpRational :: IncreaseWindow(Ptr<TcpSocketState> tcb,uint32_t segmentsAcked)
{
	const Whisker & current_whisker( _whiskers->use_whisker( _memory ) );

	unsigned int new_cwnd = current_whisker.window( (unsigned int)tcb->m_cWnd );

  // The range of our state space is 16384
	if ( new_cwnd > 16384 ) {
		new_cwnd = 16384;
	}

	tcb->m_cWnd = new_cwnd;

}
uint32_t
TcpRational::GetSsThresh (Ptr<const TcpSocketState> state,
                         uint32_t bytesInFlight)
{
  NS_LOG_FUNCTION (this << state << bytesInFlight);

  return std::max (2 * state->m_segmentSize, bytesInFlight / 2);
}
std::string
TcpRational::GetName () const
{
  return "TcpRational";
}


} // namespace ns3

/* -*- Mode:C++; c-file-style:"gnu"; indent-tabs-mode:nil; -*- */
/*
 *  Copyright (c) 2007,2008, 2009 INRIA, UDcast
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
 * Author: Mohamed Amine Ismail <amine.ismail@sophia.inria.fr>
 *                              <amine.ismail@udcast.com>
 */

#ifndef V2P_UDP_TRACE_CLIENT_H
#define V2P_UDP_TRACE_CLIENT_H

#include "ns3/application.h"
#include "ns3/event-id.h"
#include "ns3/ptr.h"
#include "ns3/ipv4-address.h"
#include <vector>

namespace ns3 {

class Socket;
class Packet;

/**
 * \ingroup udpclientserver
 *
 * \brief A trace based streamer
 *
 * Sends UDP packets based on a trace file of an MPEG4 stream
 * trace files could be downloaded form:
 * http://www2.tkn.tu-berlin.de/research/trace/ltvt.html (the 2 first lines of
 * the file should be removed)
 * A valid trace file is a file with 4 columns:
 * \li -1- the first one represents the frame index
 * \li -2- the second one indicates the type of the frame: I, P or B
 * \li -3- the third one indicates the time on which the frame was generated by the encoder (integer, milliseconds)
 * \li -4- the fourth one indicates the frame size in byte
 *
 * If no valid MPEG4 trace file is provided to the application the trace from
 * g_defaultEntries array will be loaded.
 *
 * Also note that:
 * \li -1- consecutive 'B' frames are sent together,
 * \li -2- any trace file is (by default) read again once finished (loop).
 *
 * The latter behavior can be changed through the "TraceLoop" attribute.
 */
class V2PCollisionTraceClient : public Application
{
public:
  /**
   * \brief Get the type ID.
   * \return the object TypeId
   */
  static TypeId GetTypeId (void);

  V2PCollisionTraceClient ();

  /**
   * \brief Creates a traceBasedStreamer application
   * \param ip the destination ip address to which the stream will be sent
   * \param port the destination udp port to which the stream will be sent
   * \param traceFile a path to an MPEG4 trace file formatted as follows:
   *  FrameNo Frametype   Time[ms]    Length [byte]
   *  FrameNo Frametype   Time[ms]    Length [byte]
   *  ...
   *
   *
   */
  V2PCollisionTraceClient (Ipv4Address ip, uint16_t port, char *traceFile);
  ~V2PCollisionTraceClient ();

  /**
   * \brief set the remote address and port
   * \param ip remote IP address
   * \param port remote port
   */
  void SetRemote (Address ip, uint16_t port);
  /**
   * \brief set the remote address
   * \param addr remote address
   */
  void SetRemote (Address addr);

  /**
   * \brief Set the trace file to be used by the application
   * \param filename a path to an MPEG4 trace file formatted as follows:
   *  Frame No Frametype   Time[ms]    Length [byte]
   *  Frame No Frametype   Time[ms]    Length [byte]
   *  ...
   */
  void SetTraceFile (std::string filename);

  /**
   * \brief Return the maximum packet size
   * \return the maximum packet size
   */
  uint16_t GetMaxPacketSize (void);

  /**
   * \brief Set the maximum packet size
   * \param maxPacketSize The maximum packet size
   */
  void SetMaxPacketSize (uint16_t maxPacketSize);

  /**
   * \brief Set the trace loop flag
   * \param traceLoop true if the trace should be re-used
   */
  void SetTraceLoop (bool traceLoop);

protected:
  virtual void DoDispose (void);

private:
  /**
   * \brief Load a trace file
   * \param filename the trace file path
   */
  void LoadTrace (std::string filename);
  /**
   * \brief Load the default trace
   */
  void LoadDefaultTrace (void);
  virtual void StartApplication (void);
  virtual void StopApplication (void);

  /**
   * \brief Send a packet
   */
  void Send (void);
  /**
   * \brief Send a packet of a given size
   * \param size the packet size
   */
  void SendPacket (uint32_t size);

  /**
   * \brief Entry to send.
   *
   * Each entry represents an MPEG frame
   */
  struct TraceEntry
  {
    uint32_t timeToSend; //!< Time to send the frame
    uint32_t packetSize; //!< Size of the frame
    char frameType; //!< Frame type (I, P or B)
  };

  uint32_t m_sent; //!< Counter for sent packets
  Ptr<Socket> m_socket; //!< Socket
  Address m_peerAddress; //!< Remote peer address
  uint16_t m_peerPort; //!< Remote peer port
  EventId m_sendEvent; //!< Event to send the next packet

  std::vector<struct TraceEntry> m_entries; //!< Entries in the trace to send
  uint32_t m_currentEntry; //!< Current entry index
  static struct TraceEntry g_defaultEntries[]; //!< Default trace to send
  uint16_t m_maxPacketSize; //!< Maximum packet size to send (including the SeqTsHeader)
  bool m_traceLoop; //!< Loop through the trace file
};

} // namespace ns3

#endif /* UDP_TRACE_CLIENT_H */

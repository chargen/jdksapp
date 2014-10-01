/*
 Copyright (c) 2014, J.D. Koftinoff Software, Ltd.
 All rights reserved.

 Redistribution and use in source and binary forms, with or without
 modification, are permitted provided that the following conditions are met:

 * Redistributions of source code must retain the above copyright notice, this
 list of conditions and the following disclaimer.

 * Redistributions in binary form must reproduce the above copyright notice,
 this list of conditions and the following disclaimer in the documentation
 and/or other materials provided with the distribution.

 THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
 FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
 SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
 CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
 OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#include "jdksapp_world.h"
#include "jdksapc.h"

void jdksapc_init( struct jdksapc *self,
                   struct jdksnet_stream_slots *server_stream,
                   struct jdksnet_packet_slots *client_packets )
{
    self->m_server_stream = server_stream;
    self->m_server_stream_events.m_target = self;
    self->m_server_stream_events.readable = jdksapc_server_stream_readable;
    self->m_server_stream_events.connected = jdksapc_server_stream_connected;
    self->m_server_stream_events.writable = jdksapc_server_stream_writable;
    self->m_server_stream_events.closed = jdksapc_server_stream_closed;
    self->m_server_stream_events.tick = jdksapc_server_stream_tick;

    self->m_client_packet = client_packets;
    self->m_client_packet_events.m_target = self;
    self->m_client_packet_events.closed = jdksapc_client_packet_closed;
    self->m_client_packet_events.link_down = jdksapc_client_packet_link_down;
    self->m_client_packet_events.link_up = jdksapc_client_packet_link_up;
    self->m_client_packet_events.readable = jdksapc_client_packet_readable;
    self->m_client_packet_events.writable = jdksapc_client_packet_writable;
    self->m_client_packet_events.tick = jdksapc_client_packet_tick;

    self->closeTcpConnection = jdksapc_CloseTcpConnection;
    self->connectToProxy = jdksapc_ConnectToProxy;
    self->getHttpResponse = jdksapc_GetHttpResponse;
    self->initialize = jdksapc_Initialize;
    self->notifyLinkStatus = jdksapc_NotifyLinkStatus;
    self->processMsg = jdksapc_ProcessMsg;
    self->sendHttpRequest = jdksapc_SendHttpRequest;
    self->sendIdRequest = jdksapc_SendIdRequest;
    self->sendMsgToAps = jdksapc_SendMsgToAps;
    self->sendNopToAps = jdksapc_SendNopToAps;
    self->notifyNewEntityId = jdksapc_NotifyNewEntityId;
}

void jdksapc_terminate( struct jdksapc *self ) { /* Nothing to do here */}

void jdksapc_start( struct jdksapc *self,
                    struct jdksapc_Addr const *addr,
                    struct jdksavdecc_eui48 primaryMac,
                    struct jdksavdecc_eui64 preferred_entity_id )
{
    self->m_addr = *addr;
    self->m_primaryMac = primaryMac;
    self->m_entityId = preferred_entity_id;
    jdksapc_goto_state_BEGIN( self );
}

void jdksapc_finish( struct jdksapc *self ) { self->m_finished = true; }

void jdksapc_server_stream_readable( struct jdksnet_stream_signals *self_, const struct jdksavdecc_frame *frame )
{
    struct jdksapc *self = (struct jdksapc *)self_->m_target;
}

void jdksapc_server_stream_connected( struct jdksnet_stream_signals *self_,
                                      const struct sockaddr *local_addr,
                                      socklen_t local_addr_len,
                                      const struct sockaddr *remote_addr,
                                      socklen_t remote_addr_len )
{
    struct jdksapc *self = (struct jdksapc *)self_->m_target;
}

void jdksapc_server_stream_writable( struct jdksnet_stream_signals *self_ )
{
    struct jdksapc *self = (struct jdksapc *)self_->m_target;
}

void jdksapc_server_stream_closed( struct jdksnet_stream_signals *self_ )
{
    struct jdksapc *self = (struct jdksapc *)self_->m_target;
}

void jdksapc_server_stream_tick( struct jdksnet_stream_signals *self_, jdksavdecc_timestamp_in_microseconds timestamp )
{
    struct jdksapc *self = (struct jdksapc *)self_->m_target;
}

void jdksapc_client_packet_link_up( struct jdksnet_packet_signals *self_, uint64_t bps, struct jdksavdecc_eui48 link_addr )
{
    struct jdksapc *self = (struct jdksapc *)self_->m_target;
}

void jdksapc_client_packet_link_down( struct jdksnet_packet_signals *self_, uint64_t bps, struct jdksavdecc_eui48 link_addr )
{
    struct jdksapc *self = (struct jdksapc *)self_->m_target;
}

void jdksapc_client_packet_readable( struct jdksnet_packet_signals *self_, const struct jdksavdecc_frame *frame )
{
    struct jdksapc *self = (struct jdksapc *)self_->m_target;
}

void jdksapc_client_packet_writable( struct jdksnet_packet_signals *self_ )
{
    struct jdksapc *self = (struct jdksapc *)self_->m_target;
}

void jdksapc_client_packet_closed( struct jdksnet_packet_signals *self_ )
{
    struct jdksapc *self = (struct jdksapc *)self_->m_target;
}

void jdksapc_client_packet_tick( struct jdksnet_packet_signals *self_, jdksavdecc_timestamp_in_microseconds timestamp )
{
    struct jdksapc *self = (struct jdksapc *)self_->m_target;
}

void jdksapc_CloseTcpConnection( struct jdksapc *self ) { /* TODO */}

void jdksapc_ConnectToProxy( struct jdksapc *self, struct jdksapc_Addr const *addr ) { /* TODO */}

bool jdksapc_GetHttpResponse( struct jdksapc *self )
{
    /* TODO */
    return false;
}

void jdksapc_Initialize( struct jdksapc *self )
{
    /* See IEEE Std 1722.1 Annex C.5.3.2.4 */
    self->m_apcMsgOut = false;
    self->m_apsMsgIn = false;
    self->m_finished = false;
    self->m_idAssigned = false;
    self->m_incomingTcpClosed = false;
    self->m_linkStatusMsg = false;
    self->m_responseValid = false;
    self->m_tcpConnected = false;
}

void jdksapc_NotifyLinkStatus( struct jdksapc *self, struct jdksavdecc_appdu const *linkMsg )
{
    /* TODO This is normally overridden by application */
}

void jdksapc_ProcessMsg( struct jdksapc *self, struct jdksavdecc_appdu const *apsMsg )
{
    /* TODO This is normally overridden by application */
}

void jdksapc_NotifyNewEntityId( struct jdksapc *self, struct jdksavdecc_eui64 entity_id )
{
    /* TODO This is normally overriden by application */
}

void jdksapc_SendIdRequest( struct jdksapc *self, struct jdksavdecc_eui48 primaryMac, struct jdksavdecc_eui64 entity_id )
{
    /* TODO Form and Send ID Request */
}

void jdksapc_SendHttpRequest( struct jdksapc *self, struct jdksapc_Addr const *addr ) { /* TODO Form and send HTTP request */}

void jdksapc_SendMsgToAps( struct jdksapc *self, struct jdksavdecc_appdu const *apcMsg ) { /* TODO form and send apcMsg */}

void jdksapc_SendNopToAps( struct jdksapc *self ) { /* TODO form and semd a Nop msg */}

void jdksapc_execute_state( struct jdksapc *self )
{
    switch ( self->m_state )
    {
    case jdksapc_state_BEGIN:
        jdksapc_execute_state_BEGIN( self );
        break;
    case jdksapc_state_INITIALIZE:
        jdksapc_execute_state_INITIALIZE( self );
        break;
    case jdksapc_state_WAIT_FOR_CONNECT:
        jdksapc_execute_state_WAIT_FOR_CONNECT( self );
        break;
    case jdksapc_state_ACCEPT:
        jdksapc_execute_state_ACCEPT( self );
        break;
    case jdksapc_state_START_TRANSFER:
        jdksapc_execute_state_START_TRANSFER( self );
        break;
    case jdksapc_state_WAITING:
        jdksapc_execute_state_WAITING( self );
        break;
    case jdksapc_state_CLOSED:
        jdksapc_execute_state_CLOSED( self );
        break;
    case jdksapc_state_LINK_STATUS:
        jdksapc_execute_state_LINK_STATUS( self );
        break;
    case jdksapc_state_RECEIVE_MSG:
        jdksapc_execute_state_RECEIVE_MSG( self );
        break;
    case jdksapc_state_SEND_MSG:
        jdksapc_execute_state_SEND_MSG( self );
        break;
    case jdksapc_state_ENTITY_ID_ASSIGNED:
        jdksapc_execute_state_ENTITY_ID_ASSIGNED( self );
        break;
    case jdksapc_state_SEND_NOP:
        jdksapc_execute_state_SEND_NOP( self );
        break;
    case jdksapc_state_FINISH:
        jdksapc_execute_state_FINISH( self );
        break;
    case jdksapc_state_END:
        jdksapc_execute_state_END( self );
        break;
    default:
        self->m_state = jdksapc_state_END;
        break;
    }
}

void jdksapc_goto_state_BEGIN( struct jdksapc *self ) { self->m_state = jdksapc_state_BEGIN; }

void jdksapc_execute_state_BEGIN( struct jdksapc *self ) { jdksapc_goto_state_INITIALIZE( self ); }

void jdksapc_goto_state_INITIALIZE( struct jdksapc *self )
{
    self->m_state = jdksapc_state_INITIALIZE;
    self->initialize( self );
    self->connectToProxy( self, &self->m_addr );
}

void jdksapc_execute_state_INITIALIZE( struct jdksapc *self ) { jdksapc_goto_state_WAIT_FOR_CONNECT( self ); }

void jdksapc_goto_state_WAIT_FOR_CONNECT( struct jdksapc *self ) { self->m_state = jdksapc_state_WAIT_FOR_CONNECT; }

void jdksapc_execute_state_WAIT_FOR_CONNECT( struct jdksapc *self )
{
    if ( self->m_tcpConnected )
    {
        jdksapc_goto_state_ACCEPT( self );
    }
    else if ( self->m_finished )
    {
        jdksapc_goto_state_FINISH( self );
    }
}

void jdksapc_goto_state_ACCEPT( struct jdksapc *self )
{
    self->m_state = jdksapc_state_ACCEPT;
    self->sendHttpRequest( self, &self->m_addr );
}

void jdksapc_execute_state_ACCEPT( struct jdksapc *self )
{
    if ( self->getHttpResponse( self ) )
    {
        jdksapc_goto_state_START_TRANSFER( self );
    }
    else
    {
        jdksapc_goto_state_CLOSED( self );
    }
}

void jdksapc_goto_state_START_TRANSFER( struct jdksapc *self )
{
    self->m_state = jdksapc_state_START_TRANSFER;
    self->sendIdRequest( self, self->m_primaryMac, self->m_entityId );
    self->m_nopTimeout = self->m_currentTime + 10000;
}

void jdksapc_execute_state_START_TRANSFER( struct jdksapc *self ) { jdksapc_goto_state_WAITING( self ); }

void jdksapc_goto_state_WAITING( struct jdksapc *self ) { self->m_state = jdksapc_state_WAITING; }

void jdksapc_execute_state_WAITING( struct jdksapc *self )
{
    if ( self->m_incomingTcpClosed )
    {
        jdksapc_goto_state_CLOSED( self );
    }
    else if ( self->m_finished )
    {
        jdksapc_goto_state_CLOSED( self );
    }
    else if ( self->m_linkStatusMsg )
    {
        jdksapc_goto_state_LINK_STATUS( self );
    }
    else if ( self->m_apsMsgIn )
    {
        jdksapc_goto_state_RECEIVE_MSG( self );
    }
    else if ( self->m_apcMsgOut )
    {
        jdksapc_goto_state_SEND_MSG( self );
    }
    else if ( self->m_idAssigned )
    {
        jdksapc_goto_state_ENTITY_ID_ASSIGNED( self );
    }
    else if ( self->m_currentTime > self->m_nopTimeout )
    {
        jdksapc_goto_state_SEND_NOP( self );
    }
}

void jdksapc_goto_state_CLOSED( struct jdksapc *self )
{
    self->m_state = jdksapc_state_CLOSED;
    self->closeTcpConnection( self );
}

void jdksapc_execute_state_CLOSED( struct jdksapc *self ) { jdksapc_goto_state_FINISH( self ); }

void jdksapc_goto_state_LINK_STATUS( struct jdksapc *self )
{
    self->m_state = jdksapc_state_LINK_STATUS;
    self->notifyLinkStatus( self, &self->m_linkMsg );
    self->m_linkStatusMsg = false;
}

void jdksapc_execute_state_LINK_STATUS( struct jdksapc *self ) { jdksapc_goto_state_WAITING( self ); }

void jdksapc_goto_state_RECEIVE_MSG( struct jdksapc *self )
{
    self->m_state = jdksapc_state_RECEIVE_MSG;
    self->processMsg( self, &self->m_apsMsg );
    self->m_apsMsgIn = false;
}

void jdksapc_execute_state_RECEIVE_MSG( struct jdksapc *self ) { jdksapc_goto_state_WAITING( self ); }

void jdksapc_goto_state_SEND_MSG( struct jdksapc *self )
{
    self->m_state = jdksapc_state_SEND_MSG;
    self->sendMsgToAps( self, &self->m_apcMsg );
    self->m_apcMsgOut = false;
    self->m_nopTimeout = self->m_currentTime + 10000;
}

void jdksapc_execute_state_SEND_MSG( struct jdksapc *self ) { jdksapc_goto_state_WAITING( self ); }

void jdksapc_goto_state_ENTITY_ID_ASSIGNED( struct jdksapc *self )
{
    self->m_state = jdksapc_state_ENTITY_ID_ASSIGNED;
    self->m_entityId = self->m_newId;
    self->notifyNewEntityId( self, self->m_entityId );
    self->m_nopTimeout = self->m_currentTime + 10000;
}

void jdksapc_execute_state_ENTITY_ID_ASSIGNED( struct jdksapc *self ) { jdksapc_goto_state_WAITING( self ); }

void jdksapc_goto_state_SEND_NOP( struct jdksapc *self )
{
    self->m_state = jdksapc_state_SEND_NOP;
    self->sendNopToAps( self );
    self->m_nopTimeout = self->m_currentTime + 10000;
}

void jdksapc_execute_state_SEND_NOP( struct jdksapc *self ) { jdksapc_goto_state_WAITING( self ); }

void jdksapc_goto_state_FINISH( struct jdksapc *self ) { self->m_state = jdksapc_state_FINISH; }

void jdksapc_execute_state_FINISH( struct jdksapc *self ) { jdksapc_goto_state_END( self ); }

void jdksapc_goto_state_END( struct jdksapc *self ) { self->m_state = jdksapc_state_END; }

void jdksapc_execute_state_END( struct jdksapc *self ) { (void)self; /* Do Nothing */ }

bool jdksapc_send( struct jdksapc *self, struct jdksavdecc_frame const *avdecc_frame )
{
    bool r = false;

    if ( !self->m_apcMsgOut )
    {
        jdksavdecc_appdu_set_avdecc_from_apc(
            &self->m_apcMsg, avdecc_frame->dest_address, avdecc_frame->length, avdecc_frame->payload );
        self->m_apcMsgOut = true;
        r = true;
    }
    return r;
}

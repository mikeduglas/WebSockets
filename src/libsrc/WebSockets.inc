!Generated .INC file (by the Easy COM generator v 1.14)

  INCLUDE('ecom2inc.def'),ONCE
  INCLUDE('WebSockets.int'),ONCE
  INCLUDE('ecombase.inc'),ONCE

  MAP
    MODULE('WebSockets')
      ws::DebugInfo(STRING s)
    END
  END

  !-- synchronization --
  INCLUDE('CWSYNCHM.INC'),ONCE
  INCLUDE('CWSYNCHC.INC'),ONCE

IWebSocketServerClass         CLASS(EasyCOMClass), TYPE, MODULE('WebSockets.clw'), LINK('WebSockets.clw')
IWebSocketServerObj             &IWebSocketServer,PROTECTED
Construct                       PROCEDURE()
Destruct                        PROCEDURE(),DERIVED
Init                            PROCEDURE(),HRESULT,PROC,DERIVED
Init                            PROCEDURE(LONG lpInterface),HRESULT,PROC,DERIVED
Kill                            PROCEDURE(),HRESULT,PROC,DERIVED
GetInterfaceObject              PROCEDURE(),*IWebSocketServer
GetInterfaceAddr                PROCEDURE(),LONG
GetLibLocation                  PROCEDURE(),STRING,DERIVED
!Interface methods
RegisterEventHandler            PROCEDURE(*IWebSocketEvents handler),HRESULT,PROC,VIRTUAL,PROTECTED
UnregisterEventHandler          PROCEDURE(*IWebSocketEvents handler),HRESULT,PROC,VIRTUAL,PROTECTED
vWebRoot                        PROCEDURE(BSTRING webRoot),HRESULT,PROC,VIRTUAL,PROTECTED
vPort                           PROCEDURE(long port),HRESULT,PROC,VIRTUAL,PROTECTED
vCertificate                    PROCEDURE(BSTRING certFile,BSTRING certPassword),HRESULT,PROC,VIRTUAL,PROTECTED
vStart                          PROCEDURE(),HRESULT,PROC,VIRTUAL,PROTECTED
vStop                           PROCEDURE(),HRESULT,PROC,VIRTUAL,PROTECTED
vSendText                       PROCEDURE(BSTRING serviceId,BSTRING text),HRESULT,PROC,VIRTUAL,PROTECTED
vSendBinary                     PROCEDURE(BSTRING serviceId,*VARIANT payload),HRESULT,PROC,VIRTUAL,PROTECTED
vSendFile                       PROCEDURE(BSTRING serviceId,BSTRING filename),HRESULT,PROC,VIRTUAL,PROTECTED
vAbortService                   PROCEDURE(BSTRING serviceId,long closeCode),HRESULT,PROC,VIRTUAL,PROTECTED
                              END

IWebSocketClientClass         CLASS(EasyCOMClass),TYPE,MODULE('WebSockets.clw'),LINK('WebSockets.clw')
IWebSocketClientObj             &IWebSocketClient,PROTECTED
Construct                       PROCEDURE()
Destruct                        PROCEDURE(),DERIVED
Init                            PROCEDURE(),HRESULT,PROC,DERIVED
Init                            PROCEDURE(LONG lpInterface),HRESULT,PROC,DERIVED
Kill                            PROCEDURE(),HRESULT,PROC,DERIVED
GetInterfaceObject              PROCEDURE(),*IWebSocketClient
GetInterfaceAddr                PROCEDURE(),LONG
GetLibLocation                  PROCEDURE(),STRING,DERIVED
!Interface methods
RegisterEventHandler            PROCEDURE(*IWebSocketEvents handler),HRESULT,PROC,VIRTUAL,PROTECTED
UnregisterEventHandler          PROCEDURE(*IWebSocketEvents handler),HRESULT,PROC,VIRTUAL,PROTECTED
vStart                          PROCEDURE(BSTRING pUrl),HRESULT,PROC,VIRTUAL,PROTECTED
vStop                           PROCEDURE(),HRESULT,PROC,VIRTUAL,PROTECTED
vSendText                       PROCEDURE(BSTRING text),HRESULT,PROC,VIRTUAL,PROTECTED
vSendBinary                     PROCEDURE(*VARIANT payload),HRESULT,PROC,VIRTUAL,PROTECTED
vSendFile                       PROCEDURE(BSTRING filename),HRESULT,PROC,VIRTUAL,PROTECTED
                              END


WebSocketCloseCode            EQUATE(LONG)
CloseCode::Normal             EQUATE(1000)
CloseCode::GoingAway          EQUATE(1001)
CloseCode::ProtocolError      EQUATE(1002)
CloseCode::DataTypeNotSupported   EQUATE(1003)
CloseCode::Reserved           EQUATE(1004)
CloseCode::ReservedNoStatusCode   EQUATE(1005)
CloseCode::ReservedAbnormalClosure    EQUATE(1006)
CloseCode::MismatchDataNonUTF8    EQUATE(1007)
CloseCode::ViolationOfPolicy  EQUATE(1008)
CloseCode::MessageTooLarge    EQUATE(1009)
CloseCode::EndpointExpectsExtension   EQUATE(1010)
CloseCode::ServerUnexpectedCondition  EQUATE(1011)
CloseCode::ServerRegectTlsHandshake   EQUATE(1015)


IWebSocketHost                INTERFACE, TYPE
LogInfo                         PROCEDURE(STRING pMsg)
LogWarning                      PROCEDURE(STRING pMsg)
LogError                        PROCEDURE(STRING pMsg)
ConnectionOpened                PROCEDURE(STRING serviceId, STRING servicePath, STRING serviceIP)
ConnectionClose                 PROCEDURE(STRING serviceId, WebSocketCloseCode pCode, STRING pReason)
Ping                            PROCEDURE(STRING serviceId, CONST *STRING payload)
Pong                            PROCEDURE(STRING serviceId, CONST *STRING payload)
TextFrame                       PROCEDURE(STRING serviceId, STRING pText)
TextMultiFrame                  PROCEDURE(STRING serviceId, STRING pText, BOOL isLastFrame)
BinaryFrame                     PROCEDURE(STRING serviceId, CONST *STRING payload)
BinaryMultiFrame                PROCEDURE(STRING serviceId, CONST *STRING payload, BOOL isLastFrame)
FileFrame                       PROCEDURE(STRING serviceId, STRING filename, CONST *STRING filecontents)
                              END

WebSocketEvents               CLASS(CCOMUserObject), IMPLEMENTS(IWebSocketEvents), TYPE, MODULE('WebSockets.clw'), LINK('WebSockets.clw')
m_host                          &IWebSocketHost

QueryInterface                  PROCEDURE(LONG riid, *LONG ppvObject),HRESULT,DERIVED

LogInfo                         PROCEDURE(STRING par_msg),HRESULT,PROC
LogWarning                      PROCEDURE(STRING par_msg),HRESULT,PROC
LogError                        PROCEDURE(STRING par_msg),HRESULT,PROC
ConnectionOpened                PROCEDURE(STRING serviceId,STRING servicePath,STRING serviceIP),HRESULT,PROC
ConnectionClose                 PROCEDURE(STRING serviceId, WebSocketCloseCode pCode, STRING pReason),HRESULT,PROC
Ping                            PROCEDURE(STRING serviceId,CONST *STRING payload),HRESULT,PROC
Pong                            PROCEDURE(STRING serviceId,CONST *STRING payload),HRESULT,PROC
TextFrame                       PROCEDURE(STRING serviceId,STRING text),HRESULT,PROC
TextMultiFrame                  PROCEDURE(STRING serviceId,STRING text,BOOL isLastFrame),HRESULT,PROC
BinaryFrame                     PROCEDURE(STRING serviceId,CONST *STRING payload),HRESULT,PROC
BinaryMultiFrame                PROCEDURE(STRING serviceId,CONST *STRING payload,BOOL isLastFrame),HRESULT,PROC
FileFrame                       PROCEDURE(STRING serviceId,STRING filename,CONST *STRING filecontents),HRESULT,PROC
                              END

TWebSocketServer              CLASS(IWebSocketServerClass), IMPLEMENTS(IWebSocketHost), TYPE, MODULE('WebSockets.clw'), LINK('WebSockets.clw')
m_COMIniter                     &CCOMIniter, PRIVATE
m_Sink                          &WebSocketEvents, PRIVATE
!-- synchronization object
m_Locker                          &ICriticalSection, PROTECTED

Construct                       PROCEDURE()
Destruct                        PROCEDURE(), DERIVED

Init                            PROCEDURE(), HRESULT, PROC, DERIVED, PROTECTED
Kill                            PROCEDURE(), HRESULT, PROC, DERIVED, PROTECTED

WebRoot                         PROCEDURE(STRING webRoot), BOOL, PROC
Port                            PROCEDURE(LONG pPort), BOOL, PROC
Certificate                     PROCEDURE(STRING certFile, STRING certPassword), BOOL, PROC
StartServer                     PROCEDURE(), BOOL, PROC
StopServer                      PROCEDURE(), BOOL, PROC
SendText                        PROCEDURE(STRING serviceId, STRING pText), BOOL, PROC
SendBinary                      PROCEDURE(STRING serviceId, STRING payload), BOOL, PROC !- payload: byte array
SendFile                        PROCEDURE(STRING serviceId, STRING filename), BOOL, PROC

AbortClient                     PROCEDURE(STRING serviceId, WebSocketCloseCode pCode = CloseCode::Normal), BOOL, PROC

!-- logger events
LogInfo                         PROCEDURE(STRING pMsg), VIRTUAL, PROTECTED
LogWarning                      PROCEDURE(STRING pMsg), VIRTUAL, PROTECTED
LogError                        PROCEDURE(STRING pMsg), VIRTUAL, PROTECTED
!-- service events
ConnectionOpened                PROCEDURE(STRING serviceId, STRING servicePath, STRING serviceIP), VIRTUAL, PROTECTED
ConnectionClose                 PROCEDURE(STRING serviceId, WebSocketCloseCode pCode, STRING pReason), VIRTUAL, PROTECTED
Ping                            PROCEDURE(STRING serviceId, CONST *STRING payload), VIRTUAL, PROTECTED
Pong                            PROCEDURE(STRING serviceId, CONST *STRING payload), VIRTUAL, PROTECTED
TextFrame                       PROCEDURE(STRING serviceId, STRING pText), VIRTUAL, PROTECTED
TextMultiFrame                  PROCEDURE(STRING serviceId, STRING pText, BOOL isLastFrame), VIRTUAL, PROTECTED
BinaryFrame                     PROCEDURE(STRING serviceId, CONST *STRING payload), VIRTUAL, PROTECTED
BinaryMultiFrame                PROCEDURE(STRING serviceId, CONST *STRING payload, BOOL isLastFrame), VIRTUAL, PROTECTED
FileFrame                       PROCEDURE(STRING serviceId, STRING filename, CONST *STRING filecontents), VIRTUAL, PROTECTED
                              END

TWebSocketClient              CLASS(IWebSocketClientClass), IMPLEMENTS(IWebSocketHost), TYPE, MODULE('WebSockets.clw'), LINK('WebSockets.clw')
m_COMIniter                     &CCOMIniter, PRIVATE
m_Sink                          &WebSocketEvents, PRIVATE
m_IsConnected                   BOOL, PRIVATE

Construct                       PROCEDURE()
Destruct                        PROCEDURE(), DERIVED

Init                            PROCEDURE(), HRESULT, PROC, DERIVED, PROTECTED
Kill                            PROCEDURE(), HRESULT, PROC, DERIVED, PROTECTED

StartClient                     PROCEDURE(STRING pUrl), BOOL, PROC
StopClient                      PROCEDURE(), BOOL, PROC
Connected                       PROCEDURE(), BOOL

SendText                        PROCEDURE(STRING pText), BOOL, PROC
SendBinary                      PROCEDURE(STRING payload), BOOL, PROC
SendFile                        PROCEDURE(STRING filename), BOOL, PROC

!-- logger events
LogInfo                         PROCEDURE(STRING pMsg), VIRTUAL, PROTECTED
LogWarning                      PROCEDURE(STRING pMsg), VIRTUAL, PROTECTED
LogError                        PROCEDURE(STRING pMsg), VIRTUAL, PROTECTED
!-- client events
ConnectionOpened                PROCEDURE(), VIRTUAL, PROTECTED
ConnectionClose                 PROCEDURE(WebSocketCloseCode pCode, STRING pReason), VIRTUAL, PROTECTED
Ping                            PROCEDURE(CONST *STRING payload), VIRTUAL, PROTECTED
Pong                            PROCEDURE(CONST *STRING payload), VIRTUAL, PROTECTED
TextFrame                       PROCEDURE(STRING pText), VIRTUAL, PROTECTED
TextMultiFrame                  PROCEDURE(STRING pText, BOOL isLastFrame), VIRTUAL, PROTECTED
BinaryFrame                     PROCEDURE(CONST *STRING payload), VIRTUAL, PROTECTED
BinaryMultiFrame                PROCEDURE(CONST *STRING payload, BOOL isLastFrame), VIRTUAL, PROTECTED
FileFrame                       PROCEDURE(STRING filename, CONST *STRING filecontents), VIRTUAL, PROTECTED
                              END

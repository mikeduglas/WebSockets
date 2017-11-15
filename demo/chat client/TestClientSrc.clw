  PROGRAM

  PRAGMA('project(#pragma define(_SVDllMode_ => 0))')
  PRAGMA('project(#pragma define(_SVLinkMode_ => 1))')
  !- link manifest
  PRAGMA('project(#pragma link(TestClientSrc.EXE.manifest))')

  MAP
  END

  INCLUDE('WebSockets.inc')

client                        CLASS(TWebSocketClient)
ConnectionOpened                PROCEDURE(), DERIVED, PROTECTED
ConnectionClose                 PROCEDURE(WebSocketCloseCode pCode, STRING pReason), DERIVED, PROTECTED
TextFrame                       PROCEDURE(STRING pText), DERIVED, PROTECTED
LogError                        PROCEDURE(STRING pMsg), DERIVED, PROTECTED
                              END

MsgTextToSend                 STRING(256)
FileToSend                    STRING(256)

MessageQ                      QUEUE, PRE(MessageQ)
sText                           STRING(255)
                              END

host                          STRING(255)
allowUntrusted                BOOL

Window                        WINDOW('WebSockets client'),AT(,,317,208),CENTER,GRAY,SYSTEM,FONT('Micros' & |
                                'oft Sans Serif',8)
                                ENTRY(@s255),AT(10,12,149),USE(host)
                                BUTTON('Connect'),AT(164,12,50),USE(?bConnect)
                                CHECK(' Allow untrusted'),AT(229,15),USE(allowUntrusted)
                                LIST,AT(9,37,298,118),USE(?lstMessages),HVSCROLL,FROM(MessageQ)
                                PROMPT('Text:'),AT(9,170),USE(?PROMPT1)
                                ENTRY(@s255),AT(37,167,207),USE(MsgTextToSend)
                                BUTTON('Send'),AT(258,166,50),USE(?bSendText),DEFAULT
                                BUTTON('Performance test'),AT(164,183,81),USE(?bPerformanceTest),HIDE
                                BUTTON('Send file'),AT(258,184,50),USE(?bSendFile)
                              END

  CODE

  host = GETINI('server', 'host', 'ws://localhost:88/chat', '.\TestClientSrc.ini')
  allowUntrusted = GETINI('server', 'allowUntrusted', 0, '.\TestClientSrc.ini')
  
  OPEN(Window)
  ACCEPT
    CASE ACCEPTED()
    OF ?bConnect
      IF client.Connected()
        client.StopClient()
      END
      
      client.StartClient(host, allowUntrusted)

    OF ?bSendText
      IF MsgTextToSend
        IF client.SendText(MsgTextToSend)
          MessageQ:sText = '[Me] '& MsgTextToSend
          ADD(MessageQ)
          CLEAR(MsgTextToSend)
          DISPLAY()
        END
      END
      
    OF ?bSendFile
      IF FILEDIALOG(, FileToSend, 'All files|*.*', FILE:KeepDir + FILE:LongName)
        client.SendFile(FileToSend)
      END
      
    OF ?bPerformanceTest
      ! performance/memory usage test
!      LOOP i# = 1 TO 10000
!        client.SendText('Test message #'& FORMAT(i#, @n_05))
!      END
      
      FileToSend = '.\WebSockets.dll'
      LOOP i# = 1 TO 1000
        client.SendFile(FileToSend)
      END
    END
  END

  client.StopClient()


client.ConnectionOpened       PROCEDURE()
  CODE
  MessageQ:sText = '[STATE] '& 'Connection opened'
  ADD(MessageQ)
  DISPLAY(?lstMessages)
    
client.ConnectionClose        PROCEDURE(WebSocketCloseCode pCode, STRING pReason)
  CODE
  MessageQ:sText = '[STATE] '& 'Connection closed, code '& pCode
  IF pReason
    MessageQ:sText = CLIP(MessageQ:sText) &', reason "'& pReason &'"'
  END
  
  ADD(MessageQ)
  DISPLAY(?lstMessages)
    
client.TextFrame              PROCEDURE(STRING pText)
  CODE
  MessageQ:sText = '[Server] '& pText
  ADD(MessageQ)
  DISPLAY(?lstMessages)

client.LogError               PROCEDURE(STRING pMsg)
  CODE
  MessageQ:sText = '[ERROR] '& pMsg
  ADD(MessageQ)
  DISPLAY(?lstMessages)
  
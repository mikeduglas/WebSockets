# Web Sockets
Web Socket Server and Client implemented in C# and Clarion for the modern version 13 of the WebSocket protocol.

Based on CodeProject's article [WebSocket Server in C#](https://www.codeproject.com/Articles/1063910/WebSocket-Server-in-Csharp).

## WebSocket server
- SSL support

## WebSocket client
- can be written in Clarion, JavaScript, and so on.


### How to test:
- Start TestServer.exe

for web "chat" client:
- Open http://localhost:88/client.html page in web browser, file TestServer\web\client.html will be loaded;
- type something in entry field and press "Send". A text you typed in will be send to the server, server will send it back to the client in upper case;
you'll see the response in web browser.

for Clarion "chat" client:
- run TestClientSrc.exe;
- press "Connect" to connect to the server;
- send some text, server will send it back to the client in upper case;
- send a file, server will inform about file received.

for Clarion "people" client:
- run people.exe (standard app from Clarion examples);
- run another copy of people.exe from different folder (so that 2 exe copies will connect to 2 different databases PEOPLE.TPS);
- open People browse in each running copies;
- Make database changes in one of people app (insert, update or delete records). You will see a message in another running app, that there is pending changes,
and you're able to synchronize 2 databases.
Under the hood: first "people" client sends db changes to the server, the server sends these changes to all other "people" clients.


### Requirements
- C6 and higher, ABC/Legacy
- Microsoft .NET 4.0
- EasyCOM2INC v2.14 classes and templates (free download from http://ingasoftplus.com)
- Version 13 of the WebSocket protocol

### Contacts
- <mikeduglas@yandex.ru>
- <mikeduglas66@gmail.com>

### Price
50 USD (free for xUSSR group members).
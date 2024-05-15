import React, { useState, useEffect, useRef } from 'react';
import { View, Text, TextInput, Button, FlatList, StyleSheet, KeyboardAvoidingView, Platform } from 'react-native';
import { HubConnectionBuilder } from '@microsoft/signalr';

const ChatScreen = () => {
  const [connection, setConnection] = useState(null);
  const [messages, setMessages] = useState([]);
  const [inputMessage, setInputMessage] = useState('');
  const [username, setUsername] = useState('');
  const [contentSize, setContentSize] = useState(0);
  const flatListRef = useRef(null);

  useEffect(() => {
    const newConnection = new HubConnectionBuilder()
      // .withUrl("https://192.168.66.105:7030/ChatHub", {
      //   skipNegotiation: true,
      //   transport: 1, // 1 for WebSockets
      //   accessTokenFactory: async () => { return this.token}
      // })
      .withUrl("https://localhost:7030/ChatHub", {
        skipNegotiation: true,
        transport: 1, // 1 for WebSockets
        accessTokenFactory: async () => { return this.token}
      })
      .configureLogging(1) // LogLevel.Information
      .build();

    setConnection(newConnection);

    newConnection.start()
      .then(() => {
        console.log("Connected to SignalR Hub");
        getPreviousMessages();
      })
      .catch((error) => {
        console.error("Connection error:", error);
      });

    newConnection.on("ReceiveMessage", (message) => {
      setMessages((prevMessages) => [...prevMessages, message]);
    });

    return () => {
      newConnection.stop();
    };
  }, []);

  const getPreviousMessages = async () => {
    try {
      const response = await fetch('https://localhost:7030/api/Message');
      // const response = await fetch('https://172.28.176.1:7030/api/Message');
      const data = await response.json();
      setMessages(data);
    } catch (error) {
      console.error('Error fetching messages:', error);
    }
  };

  const sendMessage = () => {
    if (!connection) {
      console.error("SignalR connection not established.");
      return;
    }

    if (!username) {
      console.error("Please enter your name.");
      return;
    }

    const message = {
      text: inputMessage,
      user: username,
    };

    connection.invoke("SendMessage", message)
      .then(() => {
        setInputMessage('');
      })
      .catch((error) => {
        console.error("Error sending message:", error);
      });
  };

  const renderItem = ({ item }) => (
    <Text style={styles.message}>{item.user}: {item.text}</Text>
  );

  useEffect(() => {
    flatListRef.current.scrollToOffset({ offset: contentSize, animated: true });
  }, [contentSize]);

  return (
    <KeyboardAvoidingView
      style={styles.container}
      behavior={Platform.OS === 'ios' ? 'padding' : 'height'}
    >
      <FlatList
        ref={flatListRef}
        data={messages}
        renderItem={renderItem}
        keyExtractor={(item, index) => index.toString()}
        contentContainerStyle={styles.messagesContainer}
        onContentSizeChange={(w, h) => setContentSize(h)}
      />
      <View style={styles.inputContainer}>
        <TextInput
          style={styles.input}
          placeholder="Type your username..."
          value={username}
          onChangeText={setUsername}
        />
        <TextInput
          style={styles.input}
          placeholder="Type your message..."
          value={inputMessage}
          onChangeText={setInputMessage}
          onSubmitEditing={sendMessage}
        />
        <Button title="Send" onPress={sendMessage} />
      </View>
    </KeyboardAvoidingView>
  );
};

const styles = StyleSheet.create({
  container: {
    flex: 1,
    justifyContent: 'flex-end',
    padding: 20,
  },
  messagesContainer: {
    flexGrow: 1,
  },
  inputContainer: {
    backgroundColor: 'white',
    padding: 10,
  },
  input: {
    height: 40,
    borderColor: 'gray',
    borderWidth: 1,
    marginBottom: 10,
    padding: 10,
  },
  message: {
    fontSize: 16,
    marginBottom: 10,
  },
});

export default ChatScreen;

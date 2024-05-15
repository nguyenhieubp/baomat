import React from 'react';
import { StatusBar } from 'expo-status-bar';
import ChatScreen from './ChatScreen';
import { registerRootComponent } from 'expo';

export default function App() {
  return (
    <>
      <ChatScreen />
      <StatusBar style="auto" />
    </>
  );
}


// registerRootComponent(App);
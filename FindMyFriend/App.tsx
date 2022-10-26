import React from 'react';
import { SafeAreaView, StyleSheet, Text } from 'react-native';

import Search from './screens/Search';
import { colors } from './components/colors';
const App = () => {
  return (
    <SafeAreaView style={styles.root}>
      <Search />
    </SafeAreaView>
  );
};

const styles = StyleSheet.create({
  root: {
    flex: 1,
    backgroundColor: colors.gray
  }
});

export default App;

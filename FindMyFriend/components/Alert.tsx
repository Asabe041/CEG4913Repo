import React, { useState, FunctionComponent } from 'react';
import { View, Text } from 'react-native';

import { colors } from './colors';

interface Props {
  color: string;
}

const Alert: FunctionComponent<Props> = ({ color }) => {
  return (
    <View
      style={{
        marginTop: 20,
        width: '50%',
        height: '6%',
        backgroundColor: color,
        borderWidth: 1,
        borderRadius: 5
      }}
    >
      <Text></Text>
    </View>
  );
};
export default Alert;

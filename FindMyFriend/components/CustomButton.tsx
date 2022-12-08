import React, { FunctionComponent } from 'react';
import {
  View,
  Button,
  StyleSheet,
  GestureResponderEvent,
  Alert
} from 'react-native';

import { colors } from './colors';

interface Props {
  name: string;
  onPress: ((event: GestureResponderEvent) => void) | undefined;
}

const CustomButton: FunctionComponent<Props> = ({ name, onPress }) => {
  return (
    <View style={styles.container}>
      <Button title={name} color={colors.graydark} onPress={onPress} />
    </View>
  );
};

const styles = StyleSheet.create({
  container: {
    width: '30%',
    paddingHorizontal: 10,
    marginVertical: 10,
    backgroundColor: colors.graylight,
    borderColor: '#E8E8E8',
    borderWidth: 1,
    borderRadius: 5
  }
});

export default CustomButton;

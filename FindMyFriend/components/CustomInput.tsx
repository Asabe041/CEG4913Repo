import React, { FunctionComponent } from 'react';
import {
  View,
  Text,
  TextInput,
  StyleSheet,
  KeyboardTypeOptions
} from 'react-native';

import { colors } from './colors';

interface Props {
  beforeVal: string;
  value?: string;
  placeHolder?: string;
  keyboard?: KeyboardTypeOptions;
  setValue?: ((text: string) => void) | undefined;
}

const CustomInput: FunctionComponent<Props> = ({
  beforeVal,
  value,
  placeHolder,
  keyboard,
  setValue
}) => {
  return (
    <View style={styles.container}>
      <Text style={styles.text}> {beforeVal}:</Text>
      <TextInput
        value={value}
        onChangeText={setValue}
        placeholder={placeHolder}
        style={styles.input}
        keyboardType={keyboard}
      />
    </View>
  );
};

const styles = StyleSheet.create({
  container: {
    width: '100%',
    flexDirection: 'row',
    paddingHorizontal: 10,
    marginVertical: 5
  },

  input: {
    backgroundColor: colors.graylight,
    paddingVertical: 5,
    paddingLeft: 10,
    marginRight: 15,
    borderColor: '#E8E8E8',
    borderWidth: 1,
    borderRadius: 5,
    flex: 2
  },
  text: { paddingVertical: 5, flex: 0.4, color: colors.graydark, fontSize: 18 }
});

export default CustomInput;

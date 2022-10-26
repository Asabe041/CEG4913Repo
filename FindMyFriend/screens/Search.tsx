import React, { useState } from 'react';
import {
  View,
  Text,
  Image,
  StyleSheet,
  useWindowDimensions
} from 'react-native';

import CustomInput from '../components/CustomInput';
import CustomButton from '../components/CustomButton';
import Alert from '../components/Alert';

const Search = () => {
  const [ipAddress, setIpAddress] = useState('');
  const [port, setPort] = useState('');
  const [barColor, setBarColor] = useState('red');

  const [showImage, setShowImage] = useState(false);

  return (
    <View style={styles.root}>
      <CustomInput
        beforeVal='IP'
        placeHolder='192.168.1.1'
        value={ipAddress}
        setValue={setIpAddress}
        keyboard='numeric'
      />
      <CustomInput
        beforeVal='Port'
        placeHolder='8080'
        value={port}
        setValue={setPort}
        keyboard='numeric'
      />
      <View style={styles.row}>
        <CustomButton
          onPress={() => {
            setShowImage(!showImage);
            setBarColor('green');
          }}
        />

        {showImage && (
          <Image
            resizeMode='center'
            source={require('../assets/loading.gif')}
          />
        )}
      </View>
      <Alert color={barColor} />
      <Text style={{ position: 'absolute', bottom: 0 }}>
        All rights reserved for Group1 of CEG4913
      </Text>
    </View>
  );
};

const styles = StyleSheet.create({
  root: {
    alignItems: 'center',
    padding: 20
  },
  row: {
    width: '100%',
    alignItems: 'center',
    flexDirection: 'row',
    marginLeft: 25
  }
});

export default Search;

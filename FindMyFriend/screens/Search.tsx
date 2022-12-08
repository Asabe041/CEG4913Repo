import React, { useState } from 'react';
import { Keyboard, View, Text, Image, StyleSheet } from 'react-native';

import CustomInput from '../components/CustomInput';
import CustomButton from '../components/CustomButton';
import Alert from '../components/Alert';
import logo from '../assets/sat.png';

let intervalId: NodeJS.Timer;

const Search = () => {
  const [ipAddress, setIpAddress] = useState('');
  const [port, setPort] = useState('8081');
  const [barColor, setBarColor] = useState('red');

  const [searching, setSearching] = useState(false);
  const [error, setError] = useState(false);

  const setColors = (led: number) => {
    if (led > 1 && led < 5) {
      setBarColor('yellow');
    } else if (led == 5) {
      setBarColor('green');
    } else {
      setBarColor('red');
    }
  };

  const getLedModule = () => {
    let ipValue = 'http://' + ipAddress + ':' + port + '/ledstate';
    fetch(ipValue)
      .then(response => response.json())
      .then(led => {
        setColors(led);
        setError(false);
      })
      .catch(error => {
        setSearching(false);
        setError(true);
        setBarColor('red');
        clearInterval(intervalId);
      });
  };

  return (
    <View style={styles.root}>
      <Image style={styles.image} source={logo} />
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
          name='Search'
          onPress={() => {
            if (intervalId) {
              setSearching(false);
              clearInterval(intervalId);
            }
            setSearching(true);
            intervalId = setInterval(() => {
              getLedModule();
            }, 2000);
            Keyboard.dismiss();
          }}
        />

        {searching && (
          <Image
            resizeMode='center'
            source={require('../assets/loading.gif')}
          />
        )}
      </View>
      {error && (
        <View style={styles.row}>
          <Text style={styles.error}>
            There was an error connecting to the server. Please try again.
          </Text>
        </View>
      )}
      <View style={styles.row}>
        <CustomButton
          name='Cancel'
          onPress={() => {
            clearInterval(intervalId);
            setError(false);
            // intervalCreator(true);
            setBarColor('red');
            setSearching(false);
          }}
        />
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
  },
  error: {
    color: 'red'
  },
  image: {
    width: '70%',
    height: '40%',
    resizeMode: 'stretch'
  }
});

export default Search;

export default {
  name: 'Ground Stations',
  icon: 'wifi',
  path: '/gs/:id',
  component: 'Dashboard',
  props: {
    defaultLayout: {
      lg: [
        {
          i: 'gs-default-a',
          x: 0,
          y: 0,
          w: 4,
          h: 7,
          component: {
            name: 'AgentList',
          },
        },
        {
          i: 'gs-default-b',
          x: 4,
          y: 0,
          w: 4,
          h: 7,
          component: {
            name: 'DisplayValue',
            props: {
              name: 'beagle1 CPU',
              displayValues: [
                {
                  name: 'CPU Load',
                  nodeProcess: 'beagle1:cpu',
                  dataKey: 'device_cpu_load_000',
                  unit: '%',
                  processDataKey: (x) => x.toFixed(2),
                },
                {
                  name: 'GiB',
                  nodeProcess: 'beagle1:cpu',
                  dataKey: 'device_cpu_gib_000',
                  unit: 'GiB',
                  processDataKey: (x) => x.toFixed(2),
                },
                {
                  name: 'Max GiB',
                  nodeProcess: 'beagle1:cpu',
                  dataKey: 'device_cpu_maxgib_000',
                  unit: 'GiB',
                  processDataKey: (x) => x.toFixed(2),
                },
              ],
            },
          },
        },
      ],
    },
  },
  children: [
    {
      name: 'KCC',
      path: '/kcc',
      icon: 'cloud',
      defaultLayout: {
        lg: [
          {
            i: 'gs-masdr-a',
            x: 0,
            y: 0,
            w: 6,
            h: 6,
            component: {
              name: 'DisplayValue',
              props: {
                name: 'Uplink',
                displayValues: [
                  {
                    name: 'Base Frequency',
                    nodeProcess: 'masdr:nordiasoft',
                    dataKey: 'device_txr_freq_000',
                    unit: 'Hz',
                    processDataKey: (x) => x.toFixed(7),
                  },
                  {
                    name: 'Doppler Frequency',
                    nodeProcess: 'masdr:nordiasoft',
                    dataKey: 'dopplerTx',
                    unit: 'Hz',
                    processDataKey: (x) => x.toFixed(7),
                  },
                  {
                    name: 'Doppler Offset',
                    nodeProcess: 'masdr:nordiasoft',
                    dataKey: 'TxFrequency',
                    unit: 'Hz',
                    processDataKey: (x) => x.toFixed(7),
                  },
                ],
              },
            },
          },
          {
            i: 'gs-masdr-aa',
            x: 6,
            y: 0,
            w: 6,
            h: 6,
            component: {
              name: 'DisplayValue',
              props: {
                name: 'Downlink',
                displayValues: [
                  {
                    name: 'Base Frequency',
                    nodeProcess: 'masdr:nordiasoft',
                    dataKey: 'device_rxr_freq_000',
                    unit: 'Hz',
                    processDataKey: (x) => x.toFixed(7),
                  },
                  {
                    name: 'Doppler Frequency',
                    nodeProcess: 'masdr:nordiasoft',
                    dataKey: 'dopplerRx',
                    unit: 'Hz',
                    processDataKey: (x) => x.toFixed(7),
                  },
                  {
                    name: 'Doppler Offset',
                    nodeProcess: 'masdr:nordiasoft',
                    dataKey: 'RxFrequency',
                    unit: 'Hz',
                    processDataKey: (x) => x.toFixed(7),
                  },
                ],
              },
            },
          },
          {
            i: 'gs-masdr-b',
            x: 6,
            y: 1,
            w: 6,
            h: 6,
            component: {
              name: 'Macro',
            },
          },
          {
            i: 'gs-masdr-c',
            x: 0,
            y: 1,
            w: 6,
            h: 6,
            component: {
              name: 'Replacement',
            },
          },
          {
            i: 'gs-masdr-d',
            x: 0,
            y: 2,
            w: 12,
            h: 10,
            component: {
              name: 'Commands',
              props: {
                nodes: ['masdr'],
              },
            },
          },
          {
            i: 'gs-masdr-e',
            x: 0,
            y: 3,
            w: 12,
            h: 14,
            component: {
              name: 'SetValues',
              props: {
                name: 'Set Values',
                node: 'masdr',
                proc: 'nordiasoft',
                values: {
                  AX25Framer: [
                    'DESTINATION_CALL_SIGN',
                    'SOURCE_CALL_SIGN',
                  ],
                  Descrambler: [
                    'DESCRAMBLER_PROPERTIES:LENGTH',
                    'DESCRAMBLER_PROPERTIES:MASK',
                    'DESCRAMBLER_PROPERTIES:SEED',
                  ],
                  GmskDemodulator: [
                    'bandwidth',
                    'samplesPerSymbol',
                    'symbolsDelay',
                  ],
                  GmskModulator: [
                    'bandwidth',
                    'samplesPerSymbol',
                    'symbolsDelay',
                  ],
                  FirKaiserFilterRx: [
                    'cutoffFrequency',
                    'samplingFrequency',
                    'stopBandAttenuation',
                    'transitionBand',
                  ],
                  FirKaiserFilterTx: [
                    'cutoffFrequency',
                    'samplingFrequency',
                    'stopBandAttenuation',
                    'transitionBand',
                  ],
                  HDLCEncoder: [
                    'HDLC_ENCODER_PROPERTIES:PREAMBLE_LENGTH',
                    'HDLC_ENCODER_PROPERTIES:POSTAMBLE_LENGTH',
                    'HDLC_ENCODER_PROPERTIES:WAVEFORM',
                  ],
                  MultiStageArbResamplerRx: [
                    'resamplingRate',
                    'stopBandAttentuation',
                  ],
                  MultiStageArbResamplerTx: [
                    'resamplingRate',
                    'stopBandAttentuation',
                  ],
                  NcoMixerRx: [
                    'dopplerFrequency',
                    'offsetFrequency',
                    'samplingFrequency',
                  ],
                  NcoMixerTx: [
                    'dopplerFrequency',
                    'offsetFrequency',
                    'samplingFrequency',
                  ],
                  ParseAX25new: [
                    'PARSEAX25_PROPERTIES:RXWAVEFORM',
                  ],
                  RepackBits: [
                    'REPACK_BITS_PROPERTIES:BITS_PER_INPUT_BYTE',
                    'REPACK_BITS_PROPERTIES:BITS_PER_OUTPUT_BYTE',
                    'REPACK_BITS_PROPERTIES:ENDIANNESS',
                  ],
                  UnpackBits: [
                    'REPACK_BITS_PROPERTIES:BITS_PER_INPUT_BYTE',
                    'REPACK_BITS_PROPERTIES:BITS_PER_OUTPUT_BYTE',
                    'REPACK_BITS_PROPERTIES:ENDIANNESS',
                  ],
                  UnpackBits2: [
                    'REPACK_BITS_PROPERTIES:BITS_PER_INPUT_BYTE',
                    'REPACK_BITS_PROPERTIES:BITS_PER_OUTPUT_BYTE',
                    'REPACK_BITS_PROPERTIES:ENDIANNESS',
                  ],
                  USRP_UHD_Device: [
                    'RF_MODE',
                    'TX_CENTER_FREQUENCY',
                    'TX_HARDWARE_SAMPLE_RATE',
                    'TX_GAIN',
                    'TX_ANTENNA',
                    'RX_BUFFER_SIZE',
                    'RX_CENTER_FREQUENCY',
                    'RX_HARDWARE_SAMPLE_RATE',
                    'RX_GAIN',
                    'RX_ANTENNA',
                  ],
                  USRP_Device_Rx: [
                    'RF_MODE',
                    'TX_CENTER_FREQUENCY',
                    'TX_HARDWARE_SAMPLE_RATE',
                    'TX_GAIN',
                    'TX_ANTENNA',
                    'RX_BUFFER_SIZE',
                    'RX_CENTER_FREQUENCY',
                    'RX_HARDWARE_SAMPLE_RATE',
                    'RX_GAIN',
                    'RX_ANTENNA',
                  ],
                  USRP_Device_Tx: [
                    'RF_MODE',
                    'TX_CENTER_FREQUENCY',
                    'TX_HARDWARE_SAMPLE_RATE',
                    'TX_GAIN',
                    'TX_ANTENNA',
                    'RX_BUFFER_SIZE',
                    'RX_CENTER_FREQUENCY',
                    'RX_HARDWARE_SAMPLE_RATE',
                    'RX_GAIN',
                    'RX_ANTENNA',
                  ],
                },
              },
            },
          },
          {
            i: 'gs-masdr-f',
            x: 0,
            y: 4,
            w: 12,
            h: 7,
            component: {
              name: 'PacketActivity',
              props: {
              },
            },
          },
          {
            i: 'gs-masdr-g',
            x: 0,
            y: 5,
            w: 12,
            h: 38,
            component: {
              name: 'Globe',
              props: {
                name: 'Orbit',
                coordinateSystem: 'geodetic',
                orbits: [
                  {
                    name: 'MASDR',
                    modelFileName: 'cubesat1.glb',
                    nodeProcess: 'masdr:nordiasoft',
                    dataKey: 'target_loc_pos_eci',
                    live: true,
                    position: [21.289373, 157.917480, 350000.0],
                    geodetic: {
                      latitude: 10,
                      longitude: 10,
                    },
                    orientation: {
                      d: {
                        x: 0,
                        y: 0,
                        z: 0,
                      },
                      w: 0,
                    },
                  },
                ],
              },
            },
          },
        ],
      },
      defaultLayoutSimple: {
        lg: [
          {
            i: 'gs-simple-mc3-a',
            x: 0,
            y: 0,
            w: 6,
            h: 6,
            component: {
              name: 'DisplayValue',
              props: {
                name: 'Uplink',
                displayValues: [
                  {
                    name: 'Base Frequency',
                    nodeProcess: 'masdr:nordiasoft',
                    dataKey: 'device_txr_freq_000',
                    unit: 'Hz',
                    processDataKey: (x) => x.toFixed(7),
                  },
                  {
                    name: 'Doppler Frequency',
                    nodeProcess: 'masdr:nordiasoft',
                    dataKey: 'dopplerTx',
                    unit: 'Hz',
                    processDataKey: (x) => x.toFixed(7),
                  },
                  {
                    name: 'Doppler Offset',
                    nodeProcess: 'masdr:nordiasoft',
                    dataKey: 'TxFrequency',
                    unit: 'Hz',
                    processDataKey: (x) => x.toFixed(7),
                  },
                ],
              },
            },
          },
          {
            i: 'gs-simple-mc3-aa',
            x: 6,
            y: 0,
            w: 6,
            h: 6,
            component: {
              name: 'DisplayValue',
              props: {
                name: 'Downlink',
                displayValues: [
                  {
                    name: 'Base Frequency',
                    nodeProcess: 'masdr:nordiasoft',
                    dataKey: 'device_rxr_freq_000',
                    unit: 'Hz',
                    processDataKey: (x) => x.toFixed(7),
                  },
                  {
                    name: 'Doppler Frequency',
                    nodeProcess: 'masdr:nordiasoft',
                    dataKey: 'dopplerRx',
                    unit: 'Hz',
                    processDataKey: (x) => x.toFixed(7),
                  },
                  {
                    name: 'Doppler Offset',
                    nodeProcess: 'masdr:nordiasoft',
                    dataKey: 'RxFrequency',
                    unit: 'Hz',
                    processDataKey: (x) => x.toFixed(7),
                  },
                ],
              },
            },
          },
          {
            i: 'gs-simple-mc3-f',
            x: 0,
            y: 4,
            w: 12,
            h: 7,
            component: {
              name: 'PacketActivity',
              props: {
              },
            },
          },
          {
            i: 'gs-simple-mc3-g',
            x: 0,
            y: 5,
            w: 12,
            h: 38,
            component: {
              name: 'Globe',
              props: {
                name: 'Orbit',
                coordinateSystem: 'geodetic',
                orbits: [
                  {
                    name: 'MASDR',
                    modelFileName: 'cubesat1.glb',
                    nodeProcess: 'masdr:nordiasoft',
                    dataKey: 'target_loc_pos_eci',
                    live: true,
                    position: [21.289373, 157.917480, 350000.0],
                    geodetic: {
                      latitude: 10,
                      longitude: 10,
                    },
                    orientation: {
                      d: {
                        x: 0,
                        y: 0,
                        z: 0,
                      },
                      w: 0,
                    },
                  },
                ],
              },
            },
          },
        ],
      },
    },
    {
      name: 'MC3',
      path: '/mc3',
      icon: 'cloud',
      defaultLayout: {
        lg: [
          {
            i: 'gs-mc3-a',
            x: 0,
            y: 0,
            w: 6,
            h: 6,
            component: {
              name: 'DisplayValue',
              props: {
                name: 'Uplink',
                displayValues: [
                  {
                    name: 'Base Frequency',
                    nodeProcess: 'masdr:nordiasoft',
                    dataKey: 'device_txr_freq_000',
                    unit: 'Hz',
                    processDataKey: (x) => x.toFixed(7),
                  },
                  {
                    name: 'Doppler Frequency',
                    nodeProcess: 'masdr:nordiasoft',
                    dataKey: 'dopplerTx',
                    unit: 'Hz',
                    processDataKey: (x) => x.toFixed(7),
                  },
                  {
                    name: 'Doppler Offset',
                    nodeProcess: 'masdr:nordiasoft',
                    dataKey: 'TxFrequency',
                    unit: 'Hz',
                    processDataKey: (x) => x.toFixed(7),
                  },
                ],
              },
            },
          },
          {
            i: 'gs-mc3-aa',
            x: 6,
            y: 0,
            w: 6,
            h: 6,
            component: {
              name: 'DisplayValue',
              props: {
                name: 'Downlink',
                displayValues: [
                  {
                    name: 'Base Frequency',
                    nodeProcess: 'masdr:nordiasoft',
                    dataKey: 'device_rxr_freq_000',
                    unit: 'Hz',
                    processDataKey: (x) => x.toFixed(7),
                  },
                  {
                    name: 'Doppler Frequency',
                    nodeProcess: 'masdr:nordiasoft',
                    dataKey: 'dopplerRx',
                    unit: 'Hz',
                    processDataKey: (x) => x.toFixed(7),
                  },
                  {
                    name: 'Doppler Offset',
                    nodeProcess: 'masdr:nordiasoft',
                    dataKey: 'RxFrequency',
                    unit: 'Hz',
                    processDataKey: (x) => x.toFixed(7),
                  },
                ],
              },
            },
          },
          {
            i: 'gs-mc3-bbbbb',
            x: 0,
            y: 3,
            w: 12,
            h: 10,
            component: {
              name: 'Sequence',
              props: {
                sequences: [
                  {
                    button: 'Initialize Nordiasoft',
                    sequence: [
                      'masdr nordiasoft initialize',
                      'masdr nordiasoft app_install ~/runtime_propcube_loopback/PropCubeWaveform',
                      'masdr nordiasoft list_applications',
                      'masdr nordiasoft app_launch PropCubeWaveform',
                      'masdr nordiasoft app_start PropCubeWaveform',
                    ],
                  },
                  {
                    button: 'Shutdown Nordiasoft',
                    sequence: [
                      'masdr nordiasoft app_stop PropCubeWaveform',
                      'masdr nordiasoft app_uninstall PropCubeWaveform',
                      'masdr nordiasoft app_shutdown PropCubeWaveform',
                    ],
                  },
                ],
              },
            },
          },
          {
            i: 'gs-mc3-b',
            x: 6,
            y: 2,
            w: 6,
            h: 6,
            component: {
              name: 'Macro',
            },
          },
          {
            i: 'gs-mc3-d',
            x: 0,
            y: 4,
            w: 12,
            h: 10,
            component: {
              name: 'Commands',
              props: {
                nodes: ['masdr'],
              },
            },
          },
          {
            i: 'gs-mc3-e',
            x: 0,
            y: 5,
            w: 12,
            h: 14,
            component: {
              name: 'SetValues',
              props: {
                name: 'Set Values',
                node: 'masdr',
                proc: 'nordiasoft',
                values: {
                  AX25Framer: [
                    'DESTINATION_CALL_SIGN',
                    'SOURCE_CALL_SIGN',
                  ],
                  Descrambler: [
                    'DESCRAMBLER_PROPERTIES:LENGTH',
                    'DESCRAMBLER_PROPERTIES:MASK',
                    'DESCRAMBLER_PROPERTIES:SEED',
                  ],
                  GmskDemodulator: [
                    'bandwidth',
                    'samplesPerSymbol',
                    'symbolsDelay',
                  ],
                  GmskModulator: [
                    'bandwidth',
                    'samplesPerSymbol',
                    'symbolsDelay',
                  ],
                  FirKaiserFilterRx: [
                    'cutoffFrequency',
                    'samplingFrequency',
                    'stopBandAttenuation',
                    'transitionBand',
                  ],
                  FirKaiserFilterTx: [
                    'cutoffFrequency',
                    'samplingFrequency',
                    'stopBandAttenuation',
                    'transitionBand',
                  ],
                  HDLCEncoder: [
                    'HDLC_ENCODER_PROPERTIES:PREAMBLE_LENGTH',
                    'HDLC_ENCODER_PROPERTIES:POSTAMBLE_LENGTH',
                    'HDLC_ENCODER_PROPERTIES:WAVEFORM',
                  ],
                  MultiStageArbResamplerRx: [
                    'centerFrequency',
                    'cutoffFrequency',
                    'delay',
                    'resamplingRate',
                    'stopBandAttenuation',
                  ],
                  MultiStageArbResamplerTx: [
                    'centerFrequency',
                    'cutoffFrequency',
                    'delay',
                    'resamplingRate',
                    'stopBandAttenuation',
                  ],
                  NcoMixerRx: [
                    'dopplerFrequency',
                    'offsetFrequency',
                    'samplingFrequency',
                  ],
                  NcoMixerTx: [
                    'dopplerFrequency',
                    'offsetFrequency',
                    'samplingFrequency',
                  ],
                  ParseAX25new: [
                    'PARSEAX25_PROPERTIES:RXWAVEFORM',
                  ],
                  RepackBits: [
                    'REPACK_BITS_PROPERTIES:BITS_PER_INPUT_BYTE',
                    'REPACK_BITS_PROPERTIES:BITS_PER_OUTPUT_BYTE',
                    'REPACK_BITS_PROPERTIES:ENDIANNESS',
                  ],
                  UnpackBits: [
                    'REPACK_BITS_PROPERTIES:BITS_PER_INPUT_BYTE',
                    'REPACK_BITS_PROPERTIES:BITS_PER_OUTPUT_BYTE',
                    'REPACK_BITS_PROPERTIES:ENDIANNESS',
                  ],
                  UnpackBits2: [
                    'REPACK_BITS_PROPERTIES:BITS_PER_INPUT_BYTE',
                    'REPACK_BITS_PROPERTIES:BITS_PER_OUTPUT_BYTE',
                    'REPACK_BITS_PROPERTIES:ENDIANNESS',
                  ],
                  USRP_UHD_Device: [
                    'RF_MODE',
                    'TX_CENTER_FREQUENCY',
                    'TX_HARDWARE_SAMPLE_RATE',
                    'TX_GAIN',
                    'TX_ANTENNA',
                    'RX_BUFFER_SIZE',
                    'RX_CENTER_FREQUENCY',
                    'RX_HARDWARE_SAMPLE_RATE',
                    'RX_GAIN',
                    'RX_ANTENNA',
                  ],
                  USRP_Device_Rx: [
                    'RF_MODE',
                    'TX_CENTER_FREQUENCY',
                    'TX_HARDWARE_SAMPLE_RATE',
                    'TX_GAIN',
                    'TX_ANTENNA',
                    'RX_BUFFER_SIZE',
                    'RX_CENTER_FREQUENCY',
                    'RX_HARDWARE_SAMPLE_RATE',
                    'RX_GAIN',
                    'RX_ANTENNA',
                  ],
                  USRP_Device_Tx: [
                    'RF_MODE',
                    'TX_CENTER_FREQUENCY',
                    'TX_HARDWARE_SAMPLE_RATE',
                    'TX_GAIN',
                    'TX_ANTENNA',
                    'RX_BUFFER_SIZE',
                    'RX_CENTER_FREQUENCY',
                    'RX_HARDWARE_SAMPLE_RATE',
                    'RX_GAIN',
                    'RX_ANTENNA',
                  ],
                },
              },
            },
          },
          {
            i: 'gs-mc3-f',
            x: 0,
            y: 6,
            w: 12,
            h: 7,
            component: {
              name: 'PacketActivity',
              props: {
              },
            },
          },
          {
            i: 'gs-mc3-g',
            x: 0,
            y: 7,
            w: 12,
            h: 38,
            component: {
              name: 'Globe',
              props: {
                name: 'Orbit',
                coordinateSystem: 'geodetic',
                orbits: [
                  {
                    name: 'MASDR',
                    modelFileName: 'cubesat1.glb',
                    nodeProcess: 'masdr:nordiasoft',
                    dataKey: 'target_loc_pos_eci',
                    live: true,
                    position: [21.289373, 157.917480, 350000.0],
                    geodetic: {
                      latitude: 10,
                      longitude: 10,
                    },
                    orientation: {
                      d: {
                        x: 0,
                        y: 0,
                        z: 0,
                      },
                      w: 0,
                    },
                  },
                ],
              },
            },
          },
        ],
      },
      defaultLayoutSimple: {
        lg: [
          {
            i: 'gs-mc3-a',
            x: 0,
            y: 0,
            w: 6,
            h: 6,
            component: {
              name: 'DisplayValue',
              props: {
                name: 'Uplink',
                displayValues: [
                  {
                    name: 'Base Frequency',
                    nodeProcess: 'masdr:nordiasoft',
                    dataKey: 'device_txr_freq_000',
                    unit: 'Hz',
                    processDataKey: (x) => x.toFixed(7),
                  },
                  {
                    name: 'Doppler Frequency',
                    nodeProcess: 'masdr:nordiasoft',
                    dataKey: 'dopplerTx',
                    unit: 'Hz',
                    processDataKey: (x) => x.toFixed(7),
                  },
                  {
                    name: 'Doppler Offset',
                    nodeProcess: 'masdr:nordiasoft',
                    dataKey: 'TxFrequency',
                    unit: 'Hz',
                    processDataKey: (x) => x.toFixed(7),
                  },
                ],
              },
            },
          },
          {
            i: 'gs-mc3-aa',
            x: 6,
            y: 0,
            w: 6,
            h: 6,
            component: {
              name: 'DisplayValue',
              props: {
                name: 'Downlink',
                displayValues: [
                  {
                    name: 'Base Frequency',
                    nodeProcess: 'masdr:nordiasoft',
                    dataKey: 'device_rxr_freq_000',
                    unit: 'Hz',
                    processDataKey: (x) => x.toFixed(7),
                  },
                  {
                    name: 'Doppler Frequency',
                    nodeProcess: 'masdr:nordiasoft',
                    dataKey: 'dopplerRx',
                    unit: 'Hz',
                    processDataKey: (x) => x.toFixed(7),
                  },
                  {
                    name: 'Doppler Offset',
                    nodeProcess: 'masdr:nordiasoft',
                    dataKey: 'RxFrequency',
                    unit: 'Hz',
                    processDataKey: (x) => x.toFixed(7),
                  },
                ],
              },
            },
          },
          {
            i: 'gs-mc3-f',
            x: 6,
            y: 1,
            w: 6,
            h: 6,
            component: {
              name: 'PacketActivity',
              props: {
              },
            },
          },
          {
            i: 'gs-mc3-bbbbb',
            x: 0,
            y: 2,
            w: 12,
            h: 10,
            component: {
              name: 'Sequence',
              props: {
                sequences: [
                  {
                    button: 'Initialize Nordiasoft',
                    sequence: [
                      'masdr nordiasoft initialize',
                      'masdr nordiasoft app_install ~/runtime_propcube_loopback/PropCubeWaveform',
                      'masdr nordiasoft list_applications',
                      'masdr nordiasoft app_launch PropCubeWaveform',
                      'masdr nordiasoft app_start PropCubeWaveform',
                    ],
                  },
                  {
                    button: 'Shutdown Nordiasoft',
                    sequence: [
                      'masdr nordiasoft app_stop PropCubeWaveform',
                      'masdr nordiasoft app_uninstall PropCubeWaveform',
                      'masdr nordiasoft app_shutdown PropCubeWaveform',
                    ],
                  },
                ],
              },
            },
          },
          // {
          //   i: 'gs-mc3-bbb',
          //   x: 0,
          //   y: 3,
          //   w: 12,
          //   h: 20,
          //   component: {
          //     name: 'Chart',
          //     props: {
          //       name: 'Satellite Pass',
          //       XDataKey: 'node_utc',
          //       processXDataKey: (x) => moment.unix((((x + 2400000.5) - 2440587.5) * 86400.0))
          //        .format('YYYY-MM-DDTHH:mm:ss'),
          //       plots: [
          //         {
          //           r: [5, 4, 3, 2, 1, 0.5, 0, 5],
          //           theta: [90, 80, 70, 60, 50, 40, 0, 180],
          //           mode: 'markers+lines',
          //           type: 'scatterpolar',
          //           marker: {
          //             color: 'red',
          //           },
          //           name: '1',
          //           YDataKey: 'predicted_path',
          //           processYDataKey: (y) => y - 273.15,
          //           nodeProcess: 'beagle1:propagator',
          //           live: true,
          //         },
          //       ],
          //     },
          //   },
          // },
          {
            i: 'gs-mc3-g',
            x: 0,
            y: 5,
            w: 12,
            h: 38,
            component: {
              name: 'Globe',
              props: {
                name: 'Orbit',
                coordinateSystem: 'geodetic',
                orbits: [
                  {
                    name: 'MASDR',
                    modelFileName: 'cubesat1.glb',
                    nodeProcess: 'masdr:nordiasoft',
                    dataKey: 'target_loc_pos_eci',
                    live: true,
                    position: [21.289373, 157.917480, 350000.0],
                    geodetic: {
                      latitude: 10,
                      longitude: 10,
                    },
                    orientation: {
                      d: {
                        x: 0,
                        y: 0,
                        z: 0,
                      },
                      w: 0,
                    },
                  },
                ],
              },
            },
          },
        ],
      },
    },
  ],
};

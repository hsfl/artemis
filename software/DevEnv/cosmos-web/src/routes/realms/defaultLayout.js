import { mjdToString } from '../../utility/time';

export default {
  lg: [
    {
      i: 'satellite-default-a',
      x: 0,
      y: 0,
      w: 4,
      h: 7,
      component: {
        name: 'AgentList',
      },
    },
    {
      i: 'satellite-default-b',
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
    {
      i: 'satellite-default-d',
      x: 0,
      y: 1,
      w: 12,
      h: 10,
      component: {
        name: 'Commands',
      },
    },
    {
      i: 'satellite-default-e',
      x: 0,
      y: 2,
      w: 6,
      h: 21,
      component: {
        name: 'Globe',
        props: {
          name: 'Orbit',
          orbits: [
            {
              name: 'neutron1',
              modelFileName: 'cubesat1.glb',
              nodeProcess: 'cubesat1:propagator_simple',
              dataKey: 'node_loc_pos_eci',
              live: true,
              position: [21.289373, 157.917480, 350000.0],
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
          overlays: [
            {
              markerColor: 'RED',
              geoJson: {
                type: 'Polygon',
                coordinates: [
                  [[30, 10], [40, 40], [20, 40], [10, 20], [30, 10]],
                ],
              },
            },
          ],
        },
      },
    },
    {
      i: 'satellite-default-f',
      x: 6,
      y: 2,
      w: 6,
      h: 21,
      component: {
        name: 'Attitude',
        props: {
          attitudes: [
            {
              name: 'n1',
              nodeProcess: 'cubesat1:propagator_simple',
              dataKey: 'node_loc_att_icrf',
              quaternions: {
                d: {
                  x: 0,
                  y: 0,
                  z: 0,
                },
                w: 0,
              },
              live: true,
            },
          ],
        },
      },
    },
    {
      i: 'satellite-default-g',
      x: 0,
      y: 3,
      w: 12,
      h: 18,
      component: {
        name: 'Chart',
        props: {
          name: 'CPU',
          XDataKey: 'node_utc',
          processXDataKey: (x) => mjdToString(x),
          plots: [
            {
              x: [],
              y: [],
              type: 'scatter',
              marker: {
                color: 'red',
              },
              name: '1',
              YDataKey: 'device_cpu_load_000',
              processYDataKey: (x) => x,
              nodeProcess: 'beagle1:cpu',
              live: true,
            },
            {
              x: [],
              y: [],
              type: 'scatter',
              marker: {
                color: 'blue',
              },
              name: '2',
              YDataKey: 'device_cpu_gib_000',
              processYDataKey: (x) => x,
              nodeProcess: 'beagle1:cpu',
              live: true,
            },
            {
              x: [],
              y: [],
              type: 'scatter',
              marker: {
                color: 'orange',
              },
              name: '3',
              YDataKey: 'device_cpu_maxgib_000',
              processYDataKey: (x) => x,
              nodeProcess: 'beagle1:cpu',
              live: true,
            },
          ],
        },
      },
    },
    {
      i: 'satellite-default-h',
      x: 0,
      y: 4,
      w: 12,
      h: 18,
      component: {
        name: 'Chart',
        props: {
          name: 'EPS Buses',
          XDataKey: 'node_utc',
          processXDataKey: (x) => mjdToString(x),
          plots: [
            {
              x: [],
              y: [],
              type: 'scatter',
              marker: {
                color: 'blue',
              },
              name: '3.3V Voltage',
              YDataKey: 'device_bus_volt_002',
              nodeProcess: 'beagle1:eps',
              live: true,
            },
            {
              x: [],
              y: [],
              type: 'scatter',
              marker: {
                color: 'red',
              },
              name: '5V Voltage',
              YDataKey: 'device_bus_volt_001',
              nodeProcess: 'beagle1:eps',
              live: true,
            },
            {
              x: [],
              y: [],
              type: 'scatter',
              marker: {
                color: 'orange',
              },
              name: '12V Voltage',
              YDataKey: 'device_bus_volt_003',
              nodeProcess: 'beagle1:eps',
              live: true,
            },
            {
              x: [],
              y: [],
              type: 'scatter',
              marker: {
                color: 'red',
              },
              name: '5V Amperage',
              YDataKey: 'device_bus_amp_001',
              nodeProcess: 'beagle1:eps',
              live: true,
            },
            {
              x: [],
              y: [],
              type: 'scatter',
              marker: {
                color: 'blue',
              },
              name: '3.3V Amperage',
              YDataKey: 'device_bus_amp_002',
              nodeProcess: 'beagle1:eps',
              live: true,
            },
            {
              x: [],
              y: [],
              type: 'scatter',
              marker: {
                color: 'orange',
              },
              name: '12V Amperage',
              YDataKey: 'device_bus_amp_003',
              nodeProcess: 'beagle1:eps',
              live: true,
            },
          ],
        },
      },
    },
    {
      i: 'satellite-default-i',
      x: 0,
      y: 5,
      w: 12,
      h: 18,
      component: {
        name: 'Chart',
        props: {
          name: 'EPS Battery Charge Regulators',
          XDataKey: 'node_utc',
          processXDataKey: (x) => mjdToString(x),
          plots: [
            {
              x: [],
              y: [],
              type: 'scatter',
              marker: {
                color: 'blue',
              },
              name: 'Amp 000',
              YDataKey: 'device_bcreg_amp_000',
              nodeProcess: 'beagle1:eps',
              live: true,
            },
            {
              x: [],
              y: [],
              type: 'scatter',
              marker: {
                color: 'red',
              },
              name: 'Volt 000',
              YDataKey: 'device_bcreg_volt_000',
              nodeProcess: 'beagle1:eps',
              live: true,
            },
            {
              x: [],
              y: [],
              type: 'scatter',
              marker: {
                color: 'blue',
              },
              name: 'Amp 001',
              YDataKey: 'device_bcreg_amp_001',
              nodeProcess: 'beagle1:eps',
              live: true,
            },
            {
              x: [],
              y: [],
              type: 'scatter',
              marker: {
                color: 'red',
              },
              name: 'Volt 001',
              YDataKey: 'device_bcreg_volt_001',
              nodeProcess: 'beagle1:eps',
              live: true,
            },
            {
              x: [],
              y: [],
              type: 'scatter',
              marker: {
                color: 'blue',
              },
              name: 'Amp 002',
              YDataKey: 'device_bcreg_amp_002',
              nodeProcess: 'beagle1:eps',
              live: true,
            },
            {
              x: [],
              y: [],
              type: 'scatter',
              marker: {
                color: 'red',
              },
              name: 'Volt 002',
              YDataKey: 'device_bcreg_volt_002',
              nodeProcess: 'beagle1:eps',
              live: true,
            },
          ],
        },
      },
    },
    {
      i: 'satellite-default-j',
      x: 0,
      y: 6,
      w: 12,
      h: 18,
      component: {
        name: 'Chart',
        props: {
          name: 'EPS Battery',
          plots: [
            {
              x: [],
              y: [],
              type: 'scatter',
              marker: {
                color: 'red',
              },
              name: 'Amerage',
              YDataKey: 'device_batt_amp_000',
              nodeProcess: 'beagle1:eps',
              live: true,
            },
            {
              x: [],
              y: [],
              type: 'scatter',
              mode: 'marker',
              marker: {
                color: 'blue',
              },
              name: 'Voltage',
              YDataKey: 'device_batt_volt_000',
              nodeProcess: 'beagle1:eps',
              live: true,
            },
            {
              x: [],
              y: [],
              type: 'scatter',
              mode: 'marker',
              marker: {
                color: 'blue',
              },
              name: 'Power',
              YDataKey: 'device_batt_power_000',
              nodeProcess: 'beagle1:eps',
              live: true,
            },
          ],
        },
      },
    },
  ],
};

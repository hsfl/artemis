import { mjdToString } from '../../utility/time';

export default {
  name: 'hyti',
  path: '/hyti',
  icon: 'camera',
  defaultLayout: {
    lg: [
      {
        i: 'satellite-hyti-a',
        x: 0,
        y: 0,
        w: 4,
        h: 7,
        component: {
          name: 'AgentList',
        },
      },
      {
        i: 'satellite-hyti-bb',
        x: 4,
        y: 0,
        w: 4,
        h: 7,
        component: {
          name: 'DisplayValue',
          props: {
            name: 'Unibap CPU',
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
        i: 'satellite-hyti-d',
        x: 0,
        y: 1,
        w: 12,
        h: 10,
        component: {
          name: 'Commands',
          props: {
            nodes: ['neutron1'],
          },
        },
      },
      {
        i: 'satellite-hyti-e',
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
          },
        },
      },
      {
        i: 'satellite-hyti-f',
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
        i: 'satellite-hyti-g',
        x: 0,
        y: 3,
        w: 12,
        h: 18,
        component: {
          name: 'Chart',
          props: {
            name: 'Temperature',
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
                YDataKey: 'device_tsen_temp_001',
                processYDataKey: (x) => x - 273.15,
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
                name: '2',
                YDataKey: 'device_tsen_temp_002',
                processYDataKey: (x) => x - 273.15,
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
                name: '3',
                YDataKey: 'device_tsen_temp_003',
                processYDataKey: (x) => x - 273.15,
                nodeProcess: 'beagle1:eps',
                live: true,
              },
            ],
          },
        },
      },
      {
        i: 'satellite-hyti-h',
        x: 0,
        y: 4,
        w: 12,
        h: 18,
        component: {
          name: 'Chart',
          props: {
            name: 'Voltage',
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
                name: '5V',
                YDataKey: 'device_bus_volt_001',
                processYDataKey: (x) => x,
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
                name: '3.3V',
                YDataKey: 'device_bus_volt_002',
                processYDataKey: (x) => x,
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
                name: 'Battery Voltage',
                YDataKey: 'device_bus_volt_003',
                processYDataKey: (x) => x,
                nodeProcess: 'beagle1:eps',
                live: true,
              },
            ],
          },
        },
      },
      {
        i: 'satellite-hyti-i',
        x: 0,
        y: 5,
        w: 12,
        h: 18,
        component: {
          name: 'Chart',
          props: {
            name: 'Amperage',
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
                name: '5V',
                YDataKey: 'device_bus_amp_001',
                processYDataKey: (x) => x,
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
                name: '3.3V',
                YDataKey: 'device_bus_amp_002',
                processYDataKey: (x) => x,
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
                name: 'Battery Voltage',
                YDataKey: 'device_bus_amp_003',
                processYDataKey: (x) => x,
                nodeProcess: 'beagle1:eps',
                live: true,
              },
            ],
          },
        },
      },
      {
        i: 'satellite-hyti-j',
        x: 0,
        y: 6,
        w: 12,
        h: 18,
        component: {
          name: 'Chart',
          props: {
            name: 'Battery Health',
            plots: [
              {
                x: [],
                y: [],
                type: 'scatter',
                marker: {
                  color: 'red',
                },
                name: 'Battery Percentage',
                YDataKey: 'device_batt_percentage_000',
                processYDataKey: (x) => x,
                nodeProcess: 'neutron1:eps',
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
                name: 'Charge',
                YDataKey: 'device_batt_charge_000',
                processYDataKey: (x) => x,
                nodeProcess: 'neutron1:eps',
                live: true,
              },
            ],
          },
        },
      },
    ],
  },
};

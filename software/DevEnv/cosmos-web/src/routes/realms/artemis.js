import { mjdToString } from '../../utility/time';

export default {
	name: 'artemis',
	path: '/artemis',
	icon: 'radar-chart',
	defaultLayout: {
		lg: [
		{
			i: 'satellite-simple-artemis-a',
			x: 0,
			y: 0,
			w: 3,
			h: 7,
			component: {
				name: 'AgentList',
			},
		},
		
		
		
		
		//======================= BeagleBone =======================
		{
			i: 'satellite-simple-artemis-b',
			x: 3,
			y: 0,
			w: 3,
			h: 7,
			component: {
				name: 'DisplayValue',
				props: {
					name: 'BeagleBone',
					displayValues: [
					{
						name: 'CPU Load',
						nodeProcess: 'any',
						dataKey: 'device_cpu_load_000',
						timeDataKey: 'node_utc',
						unit: '',
						processDataKey: (x) => x.toFixed(2),
					},
					{
						name: 'CPU Utilization',
						nodeProcess: 'any',
						dataKey: 'cpu_utilization_000',
						timeDataKey: 'node_utc',
						unit: '',
						processDataKey: (x) => x.toFixed(2),
					},
					{
						name: 'Max Memory',
						nodeProcess: 'any',
						dataKey: 'device_cpu_maxgib_000',
						timeDataKey: 'node_utc',
						unit: 'GiB',
						processDataKey: (x) => x.toFixed(2),
					},
					{
						name: 'Memory Used',
						nodeProcess: 'any',
						dataKey: 'device_cpu_gib_000',
						timeDataKey: 'node_utc',
						unit: 'GiB',
						processDataKey: (x) => x.toFixed(2),
					},
					],
				},
			},
		},
		
		//======================= Raspberry Pi =======================
		{
			i: 'satellite-simple-artemis-raspi',
			x: 6,
			y: 0,
			w: 3,
			h: 7,
			component: {
				name: 'DisplayValue',
				props: {
					name: 'Raspberry Pi',
					displayValues: [
					{
						name: 'Connected',
						nodeProcess: 'cubesat:raspi',
						dataKey: 'device_cpu_uptime_000',
						timeDataKey: 'node_utc',
						unit: '',
						processDataKey: (x) => x == 0 ? "No" : "Yes",
					},
					{
						name: 'Uptime',
						nodeProcess: 'cubesat:raspi',
						dataKey: 'device_cpu_uptime_000',
						timeDataKey: 'node_utc',
						unit: '',
						processDataKey: (x) => new Date(x * 1000).toISOString().substr(11, 8),
					},
					
					{
						name: 'Temperature',
						nodeProcess: 'cubesat:temp',
						dataKey: 'device_cpu_temp_000',
						timeDataKey: 'node_utc',
						unit: ' C',
						processDataKey: (x) => (Math.round((x - 273.15) * 100) / 100).toFixed(2),
					},
					],
				},
			},
		},
		
		//======================= PyCubed =======================
		{
			i: 'satellite-simple-artemis-pycubed',
			x: 9,
			y: 0,
			w: 3,
			h: 7,
			component: {
				name: 'DisplayValue',
				props: {
					name: 'PyCubed',
					displayValues: [
					{
						name: 'Connected',
						nodeProcess: 'cubesat:pycubed',
						dataKey: 'device_cpu_uptime_001',
						timeDataKey: 'node_utc',
						unit: '',
						processDataKey: (x) => (x > 0) ? "Yes" : "No",
					},
					{
						name: 'Up Time',
						nodeProcess: 'cubesat:pycubed',
						dataKey: 'device_cpu_uptime_001',
						timeDataKey: 'node_utc',
						unit: ' C',
						processDataKey: (x) => new Date(x * 1000).toISOString().substr(11, 8),
					},
					{
						name: 'Temperature',
						nodeProcess: 'cubesat:pycubed',
						dataKey: 'device_cpu_temp_001',
						timeDataKey: 'node_utc',
						unit: ' C',
						processDataKey: (x) => (Math.round((x - 273.15) * 100) / 100).toFixed(2),
					},
					{
						name: 'Voltage',
						nodeProcess: 'cubesat:pycubed',
						dataKey: 'device_cpu_volt_001',
						timeDataKey: 'node_utc',
						unit: ' V',
						processDataKey: (x) => x.toFixed(2),
					},
					{
						name: 'Current',
						nodeProcess: 'cubesat:pycubed',
						dataKey: 'device_cpu_amp_001',
						timeDataKey: 'node_utc',
						unit: ' A',
						processDataKey: (x) => x.toFixed(2),
					},
					{
						name: 'Memory Use',
						nodeProcess: 'cubesat:pycubed',
						dataKey: 'device_cpu_gib_001',
						timeDataKey: 'node_utc',
						unit: ' GiB',
						processDataKey: (x) => x.toFixed(2),
					},
					{
						name: 'Max Memory',
						nodeProcess: 'cubesat:pycubed',
						dataKey: 'device_cpu_maxgib_001',
						timeDataKey: 'node_utc',
						unit: ' GiB',
						processDataKey: (x) => x.toFixed(2),
					},
					],
				},
			},
		},
		
		//======================= Power =======================
		{
			i: 'satellite-simple-artemis-ba',
			x: 0,
			y: 7,
			w: 3,
			h: 7,
			component: {
				name: 'DisplayValue',
				props: {
					name: 'Power',
					displayValues: [
					{
						name: 'Battery Capacity',
						nodeProcess: 'cubesat:pycubed',
						dataKey: 'node_battcap',
						timeDataKey: 'node_utc',
						unit: ' Wh',
						processDataKey: (x) => x.toFixed(2),
					},
					{
						name: 'Battery Percent',
						nodeProcess: 'cubesat:pycubed',
						dataKey: 'device_batt_percentage_000',
						timeDataKey: 'node_utc',
						unit: ' %',
						processDataKey: (x) => x.toFixed(2),
					},
					{
						name: 'Battery Voltage',
						nodeProcess: 'cubesat:pycubed',
						dataKey: 'device_batt_volt_000',
						timeDataKey: 'node_utc',
						unit: ' V',
						processDataKey: (x) => x.toFixed(2),
					},
					{
						name: 'Battery Current',
						nodeProcess: 'cubesat:pycubed',
						dataKey: 'device_batt_amp_000',
						timeDataKey: 'node_utc',
						unit: ' A',
						processDataKey: (x) => x.toFixed(2),
					},
					{
						name: 'Power Generation',
						nodeProcess: 'cubesat:pycubed',
						dataKey: 'node_powgen',
						timeDataKey: 'node_utc',
						unit: ' W',
						processDataKey: (x) => x.toFixed(2),
					},
					{
						name: 'Power Usage',
						nodeProcess: 'cubesat:pycubed',
						dataKey: 'node_powuse',
						timeDataKey: 'node_utc',
						unit: ' W',
						processDataKey: (x) => x.toFixed(2),
					},
					],
				},
			},
		},
		//======================= Temperature =======================
		{
			i: 'satellite-simple-artemis-temperature',
			x: 3,
			y: 7,
			w: 3,
			h: 7,
			component: {
				name: 'DisplayValue',
				props: {
					name: 'Temperature',
					displayValues: [
					{
						name: 'Sensors On',
						nodeProcess: 'cubesat:temp',
						dataKey: 'device_tsen_volt_000',
						timeDataKey: 'node_utc',
						unit: '',
						processDataKey: (x) => x > 0 ? "Yes" : "No",
					},
					{
						name: 'BeagleBone',
						nodeProcess: 'cubesat:temp',
						dataKey: 'device_tsen_temp_001',
						timeDataKey: 'node_utc',
						unit: 'C',
						processDataKey: (x) => (Math.round((x - 273.15) * 100) / 100).toFixed(2),
					},
					{
						name: 'Raspberry Pi',
						nodeProcess: 'cubesat:temp',
						dataKey: 'device_tsen_temp_002',
						timeDataKey: 'node_utc',
						unit: 'C',
						processDataKey: (x) => (Math.round((x - 273.15) * 100) / 100).toFixed(2),
					},
					{
						name: 'PyCubed',
						nodeProcess: 'cubesat:temp',
						dataKey: 'device_tsen_temp_004',
						timeDataKey: 'node_utc',
						unit: 'C',
						processDataKey: (x) => (Math.round((x - 273.15) * 100) / 100).toFixed(2),
					},
					{
						name: 'EPS PDU',
						nodeProcess: 'cubesat:temp',
						dataKey: 'device_tsen_temp_000',
						timeDataKey: 'node_utc',
						unit: 'C',
						processDataKey: (x) => (Math.round((x - 273.15) * 100) / 100).toFixed(2),
					},
					{
						name: 'Battery',
						nodeProcess: 'cubesat:temp',
						dataKey: 'device_tsen_temp_003',
						timeDataKey: 'node_utc',
						unit: 'C',
						processDataKey: (x) => (Math.round((x - 273.15) * 100) / 100).toFixed(2),
					},
					],
				},
			},
		},
		
		
		
		
		//======================= Sun Sensors =======================
		{
			i: 'satellite-simple-artemis-sunsensors',
			x: 6,
			y: 7,
			w: 3,
			h: 7,
			component: {
				name: 'DisplayValue',
				props: {
					name: 'Sun Sensors',
					displayValues: [
					{
						name: 'Enabled',
						nodeProcess: 'cubesat:sunsensor',
						dataKey: 'device_ssen_volt_000',
						timeDataKey: 'node_utc',
						unit: '',
						processDataKey: (x) => x > 0 ? "Yes" : "No",
					},
					{
						name: '+X',
						nodeProcess: 'cubesat:sunsensor',
						dataKey: 'device_ssen_temp_000',
						timeDataKey: 'node_utc',
						unit: ' lx',
						processDataKey: (x) => x.toFixed(2),
					},
					{
						name: '-X',
						nodeProcess: 'cubesat:sunsensor',
						dataKey: 'device_ssen_temp_001',
						timeDataKey: 'node_utc',
						unit: ' lx',
						processDataKey: (x) => x.toFixed(2),
					},
					{
						name: '+Y',
						nodeProcess: 'cubesat:sunsensor',
						dataKey: 'device_ssen_temp_002',
						timeDataKey: 'node_utc',
						unit: ' lx',
						processDataKey: (x) => x.toFixed(2),
					},
					{
						name: '-Y',
						nodeProcess: 'cubesat:sunsensor',
						dataKey: 'device_ssen_temp_003',
						timeDataKey: 'node_utc',
						unit: ' lx',
						processDataKey: (x) => x.toFixed(2),
					},
					{
						name: '+Z',
						nodeProcess: 'cubesat:sunsensor',
						dataKey: 'device_ssen_temp_004',
						timeDataKey: 'node_utc',
						unit: ' lx',
						processDataKey: (x) => x.toFixed(2),
					},
					{
						name: '-Z',
						nodeProcess: 'cubesat:sunsensor',
						dataKey: 'device_ssen_temp_005',
						timeDataKey: 'node_utc',
						unit: ' lx',
						processDataKey: (x) => x.toFixed(2),
					},
					],
				},
			},
		},
		
		//======================= GPS =======================
		{
			i: 'satellite-simple-artemis-gps',
			x: 9,
			y: 7,
			w: 3,
			h: 7,
			component: {
				name: 'DisplayValue',
				props: {
					name: 'GPS',
					displayValues: [
					{
						name: 'Has Fix',
						nodeProcess: 'cubesat:pycubed',
						dataKey: 'device_gps_sats_used_000',
						timeDataKey: 'node_utc',
						unit: '',
						processDataKey: (x) => x > 0 ? "Yes" : "No",
					},
					{
						name: 'Latitude',
						nodeProcess: 'cubesat:pycubed',
						dataKey: 'device_gps_geods_000',
						timeDataKey: 'node_utc',
						unit: ' deg',
						processDataKey: (x) => x.lat.toFixed(4),
					},
					{
						name: 'Longitude',
						nodeProcess: 'cubesat:pycubed',
						dataKey: 'device_gps_geods_000',
						timeDataKey: 'node_utc',
						unit: ' deg',
						processDataKey: (x) => x.lon.toFixed(4),
					},
					{
						name: 'Altitude',
						nodeProcess: 'cubesat:pycubed',
						dataKey: 'device_gps_geods_000',
						timeDataKey: 'node_utc',
						unit: ' m',
						processDataKey: (x) => x.h.toFixed(2),
					},
					{
						name: 'Speed',
						nodeProcess: 'cubesat:pycubed',
						dataKey: 'device_gps_geocv_000',
						timeDataKey: 'node_utc',
						unit: ' m/s',
						processDataKey: (x) => x[0].toFixed(2),
					},
					{
						name: 'Sats Used',
						nodeProcess: 'cubesat:pycubed',
						dataKey: 'device_gps_sats_used_000',
						timeDataKey: 'node_utc',
						unit: '',
						processDataKey: (x) => x,
					},
					],
				},
			},
		},
		
		//======================= Switches =======================
		{
			i: 'satellite-simple-artemis-switches',
			x: 0,
			y: 14,
			w: 3,
			h: 7,
			component: {
				name: 'DisplayValue',
				props: {
					name: 'EPS Switches',
					displayValues: [
					{
						name: 'Temp Sensors',
						nodeProcess: 'cubesat:switch',
						dataKey: 'device_swch_volt_001',
						timeDataKey: 'node_utc',
						unit: '',
						processDataKey: (x) => x > 0 ? "On" : "Off",
					},
					{
						name: 'Sun Sensors',
						nodeProcess: 'cubesat:switch',
						dataKey: 'device_swch_volt_002',
						timeDataKey: 'node_utc',
						unit: '',
						processDataKey: (x) => x > 0 ? "On" : "Off",
					},
					{
						name: 'Heater',
						nodeProcess: 'cubesat:switch',
						dataKey: 'device_swch_volt_000',
						timeDataKey: 'node_utc',
						unit: '',
						processDataKey: (x) => x > 0 ? "On" : "Off",
					},
					],
				},
			},
		},
		
		//======================= IMU =======================
		{
			i: 'satellite-simple-artemis-imu',
			x: 3,
			y: 14,
			w: 3,
			h: 7,
			component: {
				name: 'DisplayValue',
				props: {
					name: 'IMU',
					displayValues: [
					{
						name: 'Acceleration',
						nodeProcess: 'cubesat:pycubed',
						dataKey: 'device_imu_accel_000',
						timeDataKey: 'node_utc',
						unit: ' m/s^2',
						processDataKey: (x) => '(' + (Math.round(x[0] * 100) / 100).toFixed(2) + ',' + (Math.round(x[1] * 100) / 100).toFixed(2) + ',' + (Math.round(x[2] * 100) / 100).toFixed(2) + ')',
					},
					{
						name: 'Magnetic',
						nodeProcess: 'cubesat:pycubed',
						dataKey: 'device_imu_mag_000',
						timeDataKey: 'node_utc',
						unit: ' G',
						processDataKey: (x) => '(' + (Math.round(x[0] * 100) / 100).toFixed(2) + ',' + (Math.round(x[1] * 100) / 100).toFixed(2) + ',' + (Math.round(x[2] * 100) / 100).toFixed(2) + ')',
					},
					{
						name: 'Gyroscope',
						nodeProcess: 'cubesat:pycubed',
						dataKey: 'device_imu_omega_000',
						timeDataKey: 'node_utc',
						unit: ' deg/s',
						processDataKey: (x) => '(' + (Math.round(x[0] * 100) / 100).toFixed(2) + ',' + (Math.round(x[1] * 100) / 100).toFixed(2) + ',' + (Math.round(x[2] * 100) / 100).toFixed(2) + ')',
					},
					],
				},
			},
		},
		
		
		//======================= Commands =======================
		{
			i: 'satellite-simple-artemis-commands',
			x: 0,
			y: 21,
			w: 12,
			h: 10,
			component: {
				name: 'Commands',
				props: {
					nodes: ['cubesat'],
				},
			},
		},
//		{
//			i: 'satellite-simple-artemis-e',
//			x: 0,
//			y: 8,
//			w: 6,
//			h: 21,
//			component: {
//				name: 'Globe',
//				props: {
//					name: 'Orbit',
//					orbits: [
//					{
//						name: 'artemis',
//						modelFileName: 'cubesat1.glb',
//						nodeProcess: 'cubesat:propagator_simple',
//						dataKey: 'node_loc_pos_eci',
//						live: true,
//						position: [21.289373, 157.917480, 350000.0],
//						orientation: {
//							d: {
//								x: 0,
//								y: 0,
//								z: 0,
//							},
//							w: 0,
//						},
//					},
//					],
//					overlays: [
//					{
//						color: 'CRIMSON',
//						geoJson: {
//							type: 'Polygon',
//							coordinates: [
//							[[30, 10], [40, 40], [20, 40], [10, 20], [30, 10]],
//							],
//						},
//					},
//					],
//				},
//			},
//		},
		//		{
		//			i: 'satellite-simple-artemis-f',
		//			x: 6,
		//			y: 8,
		//			w: 6,
		//			h: 21,
		//			component: {
		//				name: 'Attitude',
		//				props: {
		//					name: 'Attitude',
		//					attitudes: [
		//					{
		//						name: 'n1',
		//						nodeProcess: 'cubesat:propagator_simple',
		//						dataKey: 'node_loc_att_icrf',
		//						quaternions: {
		//							d: {
		//								x: 0,
		//								y: 0,
		//								z: 0,
		//							},
		//							w: 0,
		//						},
		//						live: true,
		//					},
		//					],
		//				},
		//			},
		//		},
		
		//======================= ?? =======================
//		{
//			i: 'satellite-simple-artemis-g',
//			x: 0,
//			y: 31,
//			w: 6,
//			h: 18,
//			component: {
//				name: 'Chart',
//				props: {
//					name: 'BeagleBone CPU',
//					XDataKey: 'node_utc',
//					processXDataKey: (x) => mjdToString(x),
//					plots: [
//					{
//						x: [],
//						y: [],
//						type: 'scatter',
//						marker: {
//							color: 'red',
//						},
//						name: 'Load',
//						YDataKey: 'device_cpu_load_000',
//						processYDataKey: (x) => x,
//						nodeProcess: 'any',
//						live: true,
//					},
//					{
//						x: [],
//						y: [],
//						type: 'scatter',
//						marker: {
//							color: 'blue',
//						},
//						name: 'Utilization',
//						YDataKey: 'cpu_utilization_000',
//						processYDataKey: (x) => x,
//						nodeProcess: 'any',
//						live: true,
//					},
//					],
//				},
//			},
//		},
		//======================= CHARTS =======================
		//======================= Temperature =======================
		{
			i: 'satellite-simple-default-tempchart',
			x: 0,
			y: 31,
			w: 6,
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
							color: 'orange',
						},
						name: 'BeagleBone',
						YDataKey: 'device_tsen_temp_001',
						timeDataKey: 'node_utc',
						processYDataKey: (x) => (x - 273.15).toFixed(2),
						nodeProcess: 'cubesat:temp',
						live: true,
					},
					{
						x: [],
						y: [],
						type: 'scatter',
						marker: {
							color: 'red',
						},
						name: 'Raspberry Pi',
						YDataKey: 'device_tsen_temp_002',
						timeDataKey: 'node_utc',
						processYDataKey: (x) => (x - 273.15).toFixed(2),
						nodeProcess: 'cubesat:temp',
						live: true,
					},
					{
						x: [],
						y: [],
						type: 'scatter',
						marker: {
							color: 'green',
						},
						name: 'PyCubed',
						YDataKey: 'device_tsen_temp_004',
						timeDataKey: 'node_utc',
						processYDataKey: (x) => (x - 273.15).toFixed(2),
						nodeProcess: 'cubesat:temp',
						live: true,
					},
					{
						x: [],
						y: [],
						type: 'scatter',
						marker: {
							color: 'blue',
						},
						name: 'EPS',
						YDataKey: 'device_tsen_temp_000',
						timeDataKey: 'node_utc',
						processYDataKey: (x) => (x - 273.15).toFixed(2),
						nodeProcess: 'cubesat:temp',
						
						live: true,
					},
					{
						x: [],
						y: [],
						type: 'scatter',
						marker: {
							color: 'yellow',
						},
						name: 'Battery',
						YDataKey: 'device_tsen_temp_003',
						timeDataKey: 'node_utc',
						processYDataKey: (x) => (x - 273.15).toFixed(2),
						nodeProcess: 'cubesat:temp',
						live: true,
					},
					],
				},
			},
		},
		//======================= Sun Sensors =======================
		{
			i: 'satellite-simple-default-sunsensorchart',
			x: 6,
			y: 31,
			w: 6,
			h: 18,
			component: {
				name: 'Chart',
				props: {
					name: 'Sun Sensors',
					XDataKey: 'node_utc',
					processXDataKey: (x) => mjdToString(x),
					plots: [
					{
						x: [],
						y: [],
						type: 'scatter',
						marker: {
							color: 'yellow',
						},
						name: 'PX',
						YDataKey: 'device_ssen_temp_000',
						processYDataKey: (x) => x.toFixed(2),
						nodeProcess: 'cubesat:sunsensor',
						live: true,
					},
					{
						x: [],
						y: [],
						type: 'scatter',
						marker: {
							color: 'blue',
						},
						name: 'MX',
						YDataKey: 'device_ssen_temp_001',
						processYDataKey: (x) => x.toFixed(2),
						nodeProcess: 'cubesat:sunsensor',
						live: true,
					},
					{
						x: [],
						y: [],
						type: 'scatter',
						marker: {
							color: 'orange',
						},
						name: 'PY',
						YDataKey: 'device_ssen_temp_002',
						processYDataKey: (x) => x.toFixed(2),
						nodeProcess: 'cubesat:sunsensor',
						live: true,
					},
					{
						x: [],
						y: [],
						type: 'scatter',
						marker: {
							color: 'green',
						},
						name: 'MY',
						YDataKey: 'device_ssen_temp_003',
						processYDataKey: (x) => x.toFixed(2),
						nodeProcess: 'cubesat:sunsensor',
						live: true,
					},
					{
						x: [],
						y: [],
						type: 'scatter',
						marker: {
							color: 'blue',
						},
						name: 'PZ',
						YDataKey: 'device_ssen_temp_004',
						processYDataKey: (x) => x.toFixed(2),
						nodeProcess: 'cubesat:sunsensor',
						live: true,
					},
					{
						x: [],
						y: [],
						type: 'scatter',
						marker: {
							color: 'purple',
						},
						name: 'MZ',
						YDataKey: 'device_ssen_temp_005',
						processYDataKey: (x) => x.toFixed(2),
						nodeProcess: 'cubesat:sunsensor',
						live: true,
					},
					],
				},
			},
		},
		],
	},
};

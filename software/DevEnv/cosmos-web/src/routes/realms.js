import defaultLayout from './realms/defaultLayout';
import neutron1 from './realms/neutron1';
import hiapo from './realms/hiapo';
import hyti from './realms/hyti';
import artemis from './realms/artemis';

export default {
  name: 'Realms',
  icon: 'rocket',
  path: '/realm/:id',
  component: 'Dashboard',
  props: {
    defaultLayout,
    realms: {
      //neutron1: ['neutron1', 'beagle1'],
      //hiapo: [],
      //hyti: [],
	artemis: ['cubesat', 'beaglebone'],
    },
  },
  children: [
    //neutron1,
    //hiapo,
    //hyti,
	artemis,
  ],
};

import {useReducer} from 'react';
import { ACTIONS } from './action'

export const useGlobalState = () => {

  const action = (state, {type, payload}) => {
    switch (type) {
      case ACTIONS.COLLAPSE:
        return {...state, ...payload};
      default:
        throw new Error();
    }
  };

  const [state, dispatch] = useReducer(action, {
    collapse: true
  });

  return {state, dispatch, ACTIONS};
};

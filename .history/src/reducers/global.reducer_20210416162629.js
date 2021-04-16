import {useReducer} from 'react';
import { ACTION } from './action'

export const useGlobalState = () => {
  const initialState = {
    collapse: true
  }
  const action = (state, {type, payload}) => {
    switch (type) {
      case ACTION.COLLAPSE:
        return {...state, ...payload};
      default:
        throw new Error();
    }
  };

  const [state, dispatch] = useReducer(action, initialState);

  return {state, dispatch, ACTION};
};

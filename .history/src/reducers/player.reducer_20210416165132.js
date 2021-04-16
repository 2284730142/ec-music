import {useReducer} from 'react';
import { ACTION } from './action'

export const playerState = () => {
/**
 * @playerState 播放器状态
 * @playerStatus 正在播放
 * @playerId 当前正在播放的音乐主键
 * @playList 当前播放列表
*/
  const initialState = {
    playerStatus: false,
    playerId: 0,
    playList: []
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

  return {state, dispatch};
};
/*
* @param reset [类型]
* @intro ...简介
* @return {...example}
* */
export const getSomething = (...reset) => {
  // data 是 post， params 自动拼接 url
  return {
    url: 'something',
    method: 'POST',
    params: {a: 1},
    data: {b: 2},
    // other axios config
  };
};

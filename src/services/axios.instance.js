import axios from 'axios';

// 初始化axios的实例
const axiosInstance = axios.create({
  baseURL: 'http://localhost:3000/api/', // 基础url配置，todo 从配置文件中拿
  timeout: 10000, // 超时时间
  timeoutErrorMessage: '刚刚的请求超时了，要不等下再试？', // 超时了返回的内容
  withCredentials: true, // 请求跨域是携带cookie
  headers: {} // 默认请求头
});

// 添加请求拦截器
axiosInstance.interceptors.request.use((config) => {
  console.log('发起了一个请求：\n', config, '\n');
  // 在发送请求之前做些什么
  return config;
}, function (error) {
  console.log('发起了一个请求, 并且发生了点错误：\n', error, '\n');
  // 对请求错误做些什么
  return Promise.reject(error);
});

// 添加响应拦截器
axiosInstance.interceptors.response.use(async (response) => {
  console.log('收到了一个响应值：\n', response, '\n');
  // 对响应数据做点什么
  return response.data;
}, function (error) {
  console.log('收到了一个响应值，但是发生了点错误：\n', error, '\n');
  // 对响应错误做点什么
  return Promise.reject(error);
});

export default axiosInstance;

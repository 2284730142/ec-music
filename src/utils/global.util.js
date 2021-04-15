export const cloneDeep = (json) => {
  let result = null;
  try {
    result = JSON.parse(JSON.stringify(json));
  } catch (e) {
    console.error(e);
  }
  return result;
};

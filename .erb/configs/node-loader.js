module.exports = function () {
  let nodeUrl = JSON.stringify(this.resourcePath);
  if (process.env.NODE_ENV === 'production') {
    nodeUrl = '__dirname +' + JSON.stringify(this.resourcePath.replace(__dirname, ''));
  }
  return 'try {global.process.dlopen(module, ' + nodeUrl + '); } catch(e) {' +
    "throw new Error('Cannot open ' + " + nodeUrl + " + ': ' + e);}";
};

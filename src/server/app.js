import express from 'express';

const expressServer = express();

expressServer.post('/api/something', (req, res) => {
  res.json({something: {c: 1}});
});

export default expressServer;


const express = require('express');
const axios = require('axios');
const FormData = require('form-data');
const fs = require('fs');
const path = require('path');


const app = express();
const port = 80;
const host = '192.168.43.150';
var albumDH = 'kidqwVuYvK49ZuZ';

app.use(express.raw({ type: 'application/octet-stream', limit: '10mb' }));

app.post('/upload', (req, res) => {
  try {
    console.log(req.body);

    // Write the image data to a file
    const imagePath = path.join(__dirname,  Date.now() + '.jpg');
    fs.writeFileSync(imagePath, req.body);


    let formData = new FormData();
    formData.append('image', fs.createReadStream(imagePath) );


    axios({
      method: 'post',
      url: 'https://api.imgur.com/3/image',
      data: formData,
      headers: {
        'Authorization': `Client-ID 276ff976ba3e4e4`,
        ...formData.getHeaders()
      },
    })
      .then(function (response) {
        console.log(response.data.data.deletehash);
        res.status(200).send(response.data.data.link);
        var image =response.data.data.deletehash;
        axios({
          method: 'post',
          url: 'https://api.imgur.com/3/album/' + albumDH + '/add',
          data: { deletehashes : image },
          headers: {
            'Authorization': `Client-ID 276ff976ba3e4e4`,
          },
        })
        
      })
      .catch(function (error) {
        console.error(error);
        res.status(500).send(error);
      });
  } catch (error) {
    console.error(error);
  }
});

app.get('/', (req, res) => {
  res.send('Servidor escuchando!');
});

app.listen(port, host, () => {
  console.log(`Server running at http://${host}:${port}`);
});

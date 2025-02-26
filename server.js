const express = require('express');
const app = express();
const { exec } = require('child_process');
const path = require('path');
const multer = require('multer');
const bodyParser = require('body-parser');
const upload = multer();

app.use(bodyParser.urlencoded({ extended: true }));
app.use(express.static('public')); // Assuming your HTML is in a 'public' 

app.get('/', (req, res) => {
    res.sendFile(path.join(__dirname, 'views', 'index.html'));
});
console.log(`${__dirname}`)

app.post('/Findroute', upload.none(), async (req, res) => {
    const source = req.body.source; // Get the source from request body
    const destination = req.body.destination; // Get the destination from request body

    console.log("Source:", source);
    console.log("Destination:", destination);

    // Provide the directory path where your C program is located
    const dirPath = '/public/executables';
    
    // Execute the C program with the provided parameters
    const command = `${__dirname}/m "${source}" "${destination}"`;
   
    exec(command, (error, stdout, stderr) => {
        if (error) {
            console.error(`Error executing C program: ${stderr}`);
            res.status(500).send('Error executing C program');
            return;
        }

        // Send the result back to the client
        res.send(stdout);
    });
});

const PORT = 3000;
app.listen(PORT, () => {
    console.log(`Server listening on port ${PORT}`);
});
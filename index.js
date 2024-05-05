// index.js
const express = require('express');
const { spawn } = require('child_process');
const app = express();
const port = 3001;

// Function to execute the C++ game logic
function startGame() {
    // Replace 'game_executable' with the actual name of your compiled C++ binary
    const gameProcess = spawn('./game_executable', []);

    gameProcess.stdout.on('data', (data) => {
        console.log(`C++ Game Output: ${data}`);
    });

    gameProcess.stderr.on('data', (data) => {
        console.error(`C++ Game Error: ${data}`);
    });

    gameProcess.on('close', (code) => {
        console.log(`C++ Game Process exited with code ${code}`);
    });
}

app.get('/', (req, res) => {
    // Serve index.html for the root route
    res.sendFile(__dirname + '/index.html');
});

app.post('/start-game', (req, res) => {
    // Start a new game by executing the C++ game logic
    startGame();
    res.send('New game started!');
});

app.listen(port, () => {
    console.log(`Server is running on port ${port}: http://localhost:${port}/`);
});

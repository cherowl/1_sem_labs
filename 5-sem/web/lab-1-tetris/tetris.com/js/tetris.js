const canvas = document.getElementById('tetris');
const context = canvas.getContext('2d');

const canvas2 = document.getElementById('nextElement');
const context2 = canvas2.getContext('2d');

let nextFigure = 'J';

const scaleSize = 20;

let down = false;

let level = 1;


const player = {
    position: {x: 0, y: 0},
    matrix: null,
    score: 0,
};

const colors = [
    null,
    '#FF0D72',
    '#0DC2FF',
    '#0DFF72',
    '#F538FF',
    '#FF8E0D',
    '#FFE138',
    '#3877FF',
];

document.addEventListener('keydown', event => {
    
    if (event.code === "ArrowLeft") {
        playerMove(-1);
    }
    else if (event.code === "ArrowRight") {
        playerMove(1);
    }
    else if (event.code === "ArrowDown") {
        playerDrop();
    }
    else if(event.code === "Space"){
        down = true;
    }
    else if(event.code === "ArrowUp"){
        playerRotate(1);
    }
});

function createMatrix(width, height) {
    const matrix = [];
    while (height--) {
        matrix.push(new Array(width).fill(0));
    }
    return matrix;
}

function createPiece(type)
{
    if (type === 'I') {
        return [
            [0, 1, 0, 0],
            [0, 1, 0, 0],
            [0, 1, 0, 0],
            [0, 1, 0, 0],
        ];
    } else if (type === 'L') {
        return [
            [0, 2, 0],
            [0, 2, 0],
            [0, 2, 2],
        ];
    } else if (type === 'J') {
        return [
            [0, 3, 0],
            [0, 3, 0],
            [3, 3, 0],
        ];
    } else if (type === 'O') {
        return [
            [4, 4],
            [4, 4],
        ];
    } else if (type === 'Z') {
        return [
            [5, 5, 0],
            [0, 5, 5],
            [0, 0, 0],
        ];
    } else if (type === 'S') {
        return [
            [0, 6, 6],
            [6, 6, 0],
            [0, 0, 0],
        ];
    } else if (type === 'T') {
        return [
            [0, 7, 0],
            [7, 7, 7],
            [0, 0, 0],
        ];
    }
}

const arena = createMatrix(12, 20);

function arenaSweep() { // del row
    next: for (let y = arena.length - 1; y > 0 ; y--) {
        for (let x = 0; x < arena[y].length; x++) {
            if(arena[y][x] === 0){
                continue next; 
            }
        }
        // array.splice(start, deleteCount[, item1[, item2[, ...]]])
        const row = arena.splice(y, 1)[0].fill(0); 
        arena.unshift(row);
        y++;

        player.score += level * 10;
    }
}

function collide(arena, player) {
    const m = player.matrix;
    const o = player.position;
    for (let y = 0; y < m.length; y++) {
        for (let x = 0; x < m[y].length; x++) {
            if(m[y][x] !== 0 &&
               (arena[y + o.y] &&
                arena[y + o.y][x + o.x]) !== 0){
                return true;
            }
        }
    }
    return false;
}

function draw() {
    context.fillStyle = '#f4ffa7';
    context.fillRect(0, 0, canvas.width, canvas.height);

    drawMatrix(arena, {x: 0, y: 0}, context, scaleSize);
    drawMatrix(player.matrix, player.position, context, scaleSize);
}

function drawNextFigure(matrix){
    context2.fillStyle = '#f4ffa7';
    context2.fillRect(0,0,canvas2.width,canvas2.height);
    drawMatrix(matrix,{x:1.2,y:0.5},context2,scaleSize);
}

function drawMatrix(matrix, offset, context, scaleSize) {
    matrix.forEach((row, y) => {
        row.forEach((value, x) => {
            if (value !== 0) {
                context.fillStyle = colors[value];
                context.strokeStyle = 'white';
                context.lineWidth = 2;
                context.fillRect(scaleSize * (x + offset.x), scaleSize * (y + offset.y), scaleSize, scaleSize);
                context.strokeRect(scaleSize * (x + offset.x), scaleSize * (y + offset.y), scaleSize, scaleSize);
            }
        });
    });
}

function merge(arena, player) {
    player.matrix.forEach((row, y) => {
        row.forEach((value, x) => {
            if (value !== 0){
                arena[y + player.position.y][x + player.position.x] = value;
            }
        });
    });
}

function playerDrop(){
    player.position.y++;
    if(collide(arena, player)){
        player.position.y--;
        merge(arena, player);
        playerReset();
        arenaSweep();
        updateScore();
        dropInterval = 1000/level;
        down = false;
    }
    dropCounter = 0;
}

function playerMove(direction){
    player.position.x += direction;
    if(collide(arena, player)){
        player.position.x -= direction;
    }
}

function playerReset() {
    const pieces = 'ILJOTSZ';

    player.matrix = createPiece(nextFigure);
    nextFigure = pieces[pieces.length * Math.random() | 0];
    drawNextFigure(createPiece(nextFigure));

    player.position.y = 0;
    player.position.x = (arena[0].length / 2 | 0) - (player.matrix[0].length / 2 | 0);

    if(collide(arena, player)) {
        arena.forEach( row => row.fill(0));
        savescore();
        player.score = 0;
        updateScore();

        window.location = "records.html";
    }
}

function playerRotate(direction) {
    const position = player.position.x;
    let offset = 1;
    rotate(player.matrix, direction);
    while (collide(arena, player)){
        player.position.x += offset;
        offset = - (offset + (offset > 0 ? 1: -1));
        if (offset > player.matrix[0].length){
            rotate(player.matrix, -direction);
            player.position.x = position;
            return;
        }
    }
}

function rotate(matrix, direction) {
    for (let y = 0; y < matrix.length; y++) {
        for (let x = 0; x < y; x++) {//transpose the matrix
            [
                matrix[x][y],
                matrix[y][x],
            ] = [
                matrix[y][x],
                matrix[x][y],
            ];
        } 
    }

    if(direction > 0){
        matrix.forEach(row  => row.reverse());
    } else{
        matrix.reverse();
    }
}


let lastTime = 0;
let dropCounter = 0;
let dropInterval = 1000;

function update(time = 0) {
    if(down){
        dropInterval = 1;
    }
    const deltaTime = time - lastTime;


    dropCounter += deltaTime;
    if(dropCounter > dropInterval) {
        playerDrop();
    }

    lastTime = time;

    draw();
    requestAnimationFrame(update);//??
}

function updateScore() {
    document.getElementById('score').innerText = "Score: " + player.score;
    document.getElementById('name').innerText = "Player: " + localStorage["username"];
    if (player.score >= level*20 ){
        dropInterval /=5;
        level++;
        document.getElementById('level').innerText ="Level: " + level;
    }
}

function savescore() {
    if (localStorage[localStorage["username"]]< player.score || (localStorage[localStorage["username"]] ===undefined)) {
        localStorage[localStorage["username"]] = player.score;
    }

}

playerReset();
updateScore();
update();

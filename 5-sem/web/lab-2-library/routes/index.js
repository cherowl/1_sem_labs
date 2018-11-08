var express = require('express');
var router = express.Router();

var books = require('../books');
books = JSON.parse(JSON.stringify(books));
var books_array = [];
for (key in books) {
    books[key].ind = Number(key);
    console.log(books[key].ind)
    books_array.push(books[key]);
}

/* GET home page. */
router.get('/', function(req, res, next) {
  res.render('index', { title: 'Welcome to the library' });
});

router.get('/library', function(req, res) {
    res.render('library', { books: books_array});
});

router.put('/library', (req, res) => {
    let body = req.body;
    console.log(req.body);
    if (!body.author || !body.name || !body.created) {
        res.status(400);
        res.json({message: "Bad Request"});
    } else {
        books_array.push({
            name: body.name,
            author: body.author,
            created: body.created,
            datereturn: '-',
            stock: true,
            taken: { date: '', whom: '' },
            ind: books_array.length
        });
    }
    res.render('library', { books: books_array});
});

router.delete('/library/:ind', (req, res)=>{
    books_array.splice(req.params.ind, 1);
    for (let i = 0; i < books_array.length; i++) {
        books_array[i].ind = i;
    }
    res.render('library', { books: books_array});
});

router.get('/library/:num(\\d+)', function(req, res) {
    const book = books_array.filter((b) => {
        if (b.ind == req.params.num) {
            return true;
        }
    });
    res.render('book', {
        name: book[0].name,
        author: book[0].author,
        created: book[0].created,
        stock: book[0].stock,
        taken_date: book[0].taken.date,
        taken_whom: book[0].taken.whom
    });
});

router.put('/library/:num(\\d+)', (req, res) => {
    let body = req.body;
    console.log(body);
    if (!body.author || !body.name || !body.created.toString().match(/^\d+$/g)) {
        res.status(400);
        res.json({message: "Bad Request"});
    } else {
        for (var i = 0; i < books_array.length; i++) {
            if (books_array[i].ind == req.params.num) {
                books_array[i].author = body.author;
                books_array[i].name = body.name;
                books_array[i].created = body.created;
                break;
            }
        }
    }

});

router.post('/library/:num(\\d+)', (req, res) => {
    let body = req.body;
    console.log("sdsd");
    if (!body.stock || !body.name_returned) { res.status(400);
        res.json({message: "Bad Request"});
    } else {
        for (var i = 0; i < books_array.length; i++) {
            if (books_array[i].ind == req.params.num) {
                if (body.stock === 'true') {
                    books_array[i].stock = false;
                    books_array[i].taken.date = body.date_returned;
                    books_array[i].taken.whom = body.name_returned;
                } else {
                    books_array[i].stock = true;
                    books_array[i].datereturn = body.date_returned;
                    books_array[i].taken.date = "";
                    books_array[i].taken.whom = "";
                }
                break;
            }
        }
    }
});


module.exports = router;
module.exports.obj = books_array;
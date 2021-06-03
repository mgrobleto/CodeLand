const { Router } = require('express')
const router = Router()
const User = require('../models/user')
const isLogged = require('../middlewares/isLogged')

router.get('/', (_, res) => {
    res.render('index')
})

router.get('/home', function (_, res){
    res.render('index')
})

router.get('/register', (_, res) => {
    res.render('user/register')
})

router.post('/register', async (req, res) => {
    const { name, email, password } = req.body
    if(!req.body.email || !req.body.password) {
        return res.redirect('/register')
    }
    if(password.length > 4) {
        const newUser = new User({name, email, password})
        newUser.password = await newUser.encryptPassword(password)
        req.session.userId = newUser._id;
        await newUser.save()
        res.redirect('/')
    }
})

router.get('/login', isLogged, (_, res) => {
    res.render('user/login')
})

router.post('/login', async (req, res) => {
    const { email, password } = req.body
    const findUser = await User.findOne({email})
    if(!findUser) {
        return res.redirect('/login')
    }
    const match = await findUser.matchPassword(password)
    if(!findUser) {
        return res.redirect('/login')
    }
    if(match) {
        req.session.userId = findUser._id;
        return res.redirect('/user/profile')
    } else {
        return res.redirect('/login')
    }
})

router.put('/update', async (req, res) => {
    const findUser = User.findById(req.params.id)
    if(req.body.name) {
        ;(await findUser).overwrite({name: req.body.name})
    }
    res.json(findUser)
})

router.get('/logout', (req, res, next) => {
    req.session.destroy(function (err) {
        if(err) {
            return next(err)
        }
        res.clearCookie('connect.sid', {path: '/'}).redirect('/login')
    })
})

module.exports = router
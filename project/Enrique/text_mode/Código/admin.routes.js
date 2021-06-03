const { Router } = require('express')
const isAdmin = require('../middlewares/isAdmin')
const AdminModel = require('../models/admin')
const UserModel = require('../models/user')
const router = Router();

router.get('/', isAdmin, async function (_, res) {
    const db = await UserModel.find({}).lean()
    res.render('admin/admin', {
        users: db
    })
})

router.get('/register', function(req, res) {
    if(!req.session.userId) {
        res.render('admin/register')
    } else {
        res.redirect('/admin/register')
    }
})

router.post('/register', async function(req, res) {
    const { username, email, password} = req.body
    if(password.length < 4) {
        res.redirect('/admin/register')
    } else {
        const emailUser = await AdminModel.findOne({email})
        if(!emailUser) {
            const newAdmin = new AdminModel({username, email, password})
            newAdmin.password = await newAdmin.encryptPassword(password)
            req.session.userId = newAdmin._id
            await newAdmin.save();
            res.redirect('/admin')
        }
    }
})

router.get('/login', function (req, res) {
    if(req.session.userId) {
        res.redirect('/admin')
    }
    res.render('admin/login')
})

router.post('/login', async function (req, res) {
    if(req.session.userId) {
        res.redirect('/admin')
    }    
    const { email, password } = req.body
    const findAdmin = await AdminModel.findOne({email})
    if(!findAdmin) {
        return res.redirect('/admin/login')
    }
    const matchPassword = await findAdmin.matchPassword(password)
    if(matchPassword) {
        req.session.userId = findAdmin._id;
        res.redirect('/admin')
    } else {
        res.redirect('/admin/login')
    }
    
})

router.get('/logout', function(req, res) {
    req.session.destroy(function (err) {
        if(err) {
            return next(err)
        }
        res.clearCookie('connect.sid', { path: '/' }).redirect('/')
        return;
    })
})

module.exports = router

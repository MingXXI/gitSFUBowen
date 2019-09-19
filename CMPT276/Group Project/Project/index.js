const express = require('express')
const path = require('path')
const PORT = process.env.PORT || 5000
const { Pool } = require('pg');

var bodyParser = require('body-parser')

const cookieParser = require('cookie-parser')
const session = require('express-session')
const sessionFiles = require('session-file-store')(session)

const pool = new Pool({
  connectionString: process.env.DATABASE_URL,
  ssl: true
});

var app = express()
express()
  .use(express.static(path.join(__dirname, 'public')))
  .use(bodyParser.json())
  .use(cookieParser('dining pal'))
  .use(session({
    secret: 'dining pal',
    //resave: true,
    saveUninitialized: false,
    store: new sessionFiles({logFn:()=>{}}),//replace the logFn option with an empty function
    cookie: { user:"default", maxAge:360000 }
  }))
  .set('views', path.join(__dirname, 'views'))
  .set('view engine', 'ejs')

  .get('/', (req, res ) => {
    //console.log("Welcome back")
    var myUser = req.session.myUser
    //var isAdmin = req.session.isAdmin
    if(myUser){
      console.log(myUser)//show session content
      if(myUser.isadmin){
        console.log("homepage_admin. adminname:"+myUser.username)
        //console.log("All users:"+req.session.allUsers)
        res.redirect('/NewUI/new_homepage.html')
      }
      else {
        console.log("homepage_user. username:"+myUser.username)
        res.redirect('/NewUI/new_homepage_user.html')
      }
    }
    else {
        //res.render('pages/index')
        res.redirect('/startpage.html')
    }
  })

  // .get('/home', (req, res ) => {//for testing
  //   //console.log("Welcome back")
  //   var myUser = req.session.myUser
  //   //var isAdmin = req.session.isAdmin
  //   if(myUser){
  //     console.log(myUser)//show session content
  //     if(myUser.isadmin){
  //       console.log("homepage_admin. adminname:"+myUser.username)
  //       //console.log("All users:"+req.session.allUsers)
  //       res.redirect('/NewUI/new_homepage.html')
  //     }
  //     else {
  //       console.log("homepage_user. username:"+myUser.username)
  //       res.redirect('/NewUI/new_homepage_user.html')
  //     }
  //   }
  //   else {
  //       //res.render('pages/index')
  //       res.redirect('/startpage.html')
  //   }
  // })

  .get('/signin', async (req,res)=>{
    try{
      const client = await pool.connect()
      var query = "select * from users where email=($1) and password=($2)";
      var info = [req.query.email, req.query.password];
      await client.query(query, info, async function(err, result){
        if (err||!result.rows[0]){
        	console.log("Query error: " + err )
          console.log(result.rows[0] )
          /*do something if Username or password incorrect
          res.send("Query error: " + err);
          */
          res.render('pages/error',{message:"E-mail or password incorrect"})
      	}
        else {
          console.log("signin succeed")

          if(result.rows[0].isadmin){//admin user
            //query = "select * from users"
            //const result = await client.query(query)
            	console.log('admin:',info[0])
              //console.log('allusers:',result2)
              //const results = { 'results': (result) ? result.rows : null}
              req.session.regenerate((err)=>{
                if(err){
                  console.log(err)
                  res.render('pages/error',{message:"Cookie function fail"})
                }
              })
              req.session.myUser = {
                username:result.rows[0].username,
                email:result.rows[0].email,
                isadmin:result.rows[0].isadmin,//true
              }
              //req.session.allUsers = { 'results': (result) ? result.rows : null}
              //console.log(results)
              res.redirect('/NewUI/new_homepage.html')

          }
          else{//regular user
          	console.log("user:",result.rows[0].username)
            req.session.regenerate((err)=>{
              if(err){
                console.log(err)
                res.render('pages/error',{message:"Cookie function fail"})
              }
            })
            req.session.myUser = {
              username:result.rows[0].username,
              email:result.rows[0].email,
              isadmin:result.rows[0].isadmin//false
              //and any other info useful
            }
            res.redirect('/NewUI/new_homepage_user.html')
          }
          client.release();
        }
        res.end()
      })
    } catch (err){
      console.error(err);//database not connected
      // res.send("DB connection error: " + err );
      res.render('pages/error',{message:"Database connection fail"})
    }
  })



  .get('/signup', async (req,res)=>{
    try{
      const client = await pool.connect()
      var query = "insert into users values($1, $2, $3, FALSE) ";
      var info = [req.query.username, req.query.password, req.query.email];
      await client.query(query, info, function(err, result){
        if (err){
          console.log("Query error: " + err );
          /*do something if username exist
          // res.send("Query error: " + err);
          */
          res.render('pages/error',{message:"E-mail already exist"})
      	}
        else {
          console.log("signup succeed")
          req.session.regenerate((err)=>{
            if(err){
              res.render('pages/error',{message:"Cookie function fail"})
              return console.log(err)
            }
          })
          req.session.myUser = {
            username:req.query.username,
            email:req.query.email,
            isadmin:false//false
            //and any other info useful
          }
          //var userinfo = {username:req.query.username, password:req.query.password, email:req.query.email, isadmin:false}
          res.redirect('/NewUI/new_homepage_user.html')
          client.release();
        }
        res.end()
      })
    } catch (err){
      console.error(err);//database not connected
      res.render('pages/error',{message:"Database connection fail"})
    }
  })



  .get('/checkLogin',(req, res)=>{
    var myUser = req.session.myUser
    if(myUser){
      console.log("user logged in. username:"+myUser.username)
      res.send({isLogin: true})
    }
    else {
      console.log("user not logged in")
      res.send({isLogin: false})
    }
  })

  .get('/getUsername',(req, res)=>{
    var myUser = req.session.myUser
    if(myUser){
      console.log("send username:"+myUser.username)
      res.send({username:myUser.username})
    }
    else {
      console.log("user not logged in")
      res.send({username:"None"})
    }
  })

  .get('/sendLocation', async (req, res)=>{
    var myUser = req.session.myUser
    if(myUser){
      try{
        const client = await pool.connect()
        var query = "update users set x=($1), y=($2) where email=($3) ";
        var info = [req.query.x, req.query.y, myUser.email];
          console.log("email: "+myUser.email)
          console.log("x: "+req.query.x)
          console.log("y: "+req.query.y)
        await client.query(query, info, function(err, result){
          if (err){
            console.log("Query error: " + err );
            //res.render('pages/error',{message:"E-mail already exist"})
        	}
          else {
            console.log("location update succeed")
            //var userinfo = {username:req.query.username, password:req.query.password, email:req.query.email, isadmin:false}
            //res.redirect('/NewUI/new_homepage_user.html')
            client.release();
          }
          res.end()
        })
      } catch (err){
        console.error(err);//database not connected
        //res.render('pages/error',{message:"Database connection fail"})
      }
    }
    else {
      console.log("user not logged in")
      //res.send({username:"None"})
    }
  })

  .get('/logout', (req, res)=>{
    req.session.destroy((err)=>{
      if(err){
        console.log("Fail to destroy cookie")
        res.render('pages/error',{message:"Fail to destroy cookie"})
      }
      console.log("logging out")
      res.clearCookie()
      res.redirect('/')
    })
  })

  .get('/deleteUser', async (req,res)=>{
    try{
      const client = await pool.connect()
      var query = "delete from users where email=($1)";
      var info = [req.query.email];
      //console.log("useremail is "+req.query)
      await client.query(query, info, function(err, result){
        if (err){
          console.log("Query error: " + err );
          /*do something if username exist
          // res.send("Query error: " + err);
          */
          res.render('pages/error',{message:"Fail to delete user"})
      	}
        else {
          console.log("delete succeed")
          //var userinfo = {username:req.query.username, password:req.query.password, email:req.query.email, isadmin:false}
          res.redirect('/database')
          client.release();
        }
        res.end()
      })
    } catch (err){
      console.error(err);//database not connected
      res.render('pages/error',{message:"Database connection fail"})
    }
  })

  .get('/database', async(req,res)=>{
    var myUser = req.session.myUser
    if(myUser && myUser.isadmin){
      console.log('get database')
      try{
        const client = await pool.connect()
        const result = await client.query('SELECT * FROM users')
        const results = {'results':(result)? result.rows:null}
        res.render('pages/table-dynamic',results)
        client.release()
      }
      catch(err){
        console.error(err)
        res.render('pages/error',{message:"Database connection fail"})
      }
    }
    else{//not admin loginned
      console.log('Not loginned or not admin')
      res.redirect('/')
    }
  })
  .listen(PORT, () => console.log(`Listening on ${ PORT }`))
  module.exports = app

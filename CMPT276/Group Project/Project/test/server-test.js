var chai = require('chai');
var chaiHttp = require('chai-http');
var server = require('../index.js');
var should = chai.should();

chai.use(chaiHttp);

describe('Users', function(){
  it('should redirect to startpage when / and not login', function(done){
    chai.request(server)
    //.send({email:"test1@sfu.ca", password:"123"})
    .get('/')
    .end(function(err, res){
      res.should.redirectTo("localhost:5000/startpage.html");
      done();
    });
  });

  it('should redirect to startpage when /home and not login', function(done){
    chai.request(server)
    //.send({email:"test1@sfu.ca", password:"123"})
    .get('/home')
    .end(function(err, res){
      res.should.redirectTo("localhost:5000/startpage.html");
      done();
    });
  });

  it('should redirect to new user HomePage when user login', function(done){
    chai.request(server)
    .get('/signin')
    .send({email:"test1@sfu.ca", password:"123"})
    .end(function(err, res){
      res.should.redirectTo("localhost:5000/NewUI/new_homepage_user.html");
      done();
    });
  });

  it('should redirect to startpage when logging out', function(done){
    chai.request(server)
    //.send({email:"test1@sfu.ca", password:"123"})
    .get('/logout')
    .end(function(err, res){
      res.should.redirectTo("localhost:5000/startpage.html");
      done();
    });
  });

  it('should redirect to new admin HomePage when admin login', function(done){
    chai.request(server)
    .get('/signin')
    .send({email:"cza94@sfu.ca", password:"segfault"})
    .end(function(err, res){
      res.should.redirectTo("localhost:5000/NewUI/new_homepage.html");
      done();
    });
  });

  it('should redirect to new user HomePage when user sign up', function(done){
    chai.request(server)
    .get('/signup')
    .send({username:"tester", email:"tester@sfu.ca", password:"123"})
    .end(function(err, res){
      res.should.redirectTo("localhost:5000/NewUI/new_homepage_user.html");
      done();
    });
  });

  it('should send isLogin:false when checkLogin', function(done){
    chai.request(server)
    //.send({username:"tester", email:"tester@sfu.ca", password:"123"})
    .get('/checkLogin')
    .end(function(err, res){
      chai.assert.equal(res.isLogin, false);
      done();
    });
  });

  it('should send None when /getUsername and not login', function(done){
    chai.request(server)
    //.send({username:"tester", email:"tester@sfu.ca", password:"123"})
    .get('/getUsername')
    .end(function(err, res){
      chai.assert.equal(res.username, "None");
      done();
    });
  });


  // it('should add a single user on POST /users', function(done){
  //   chai.request(server).get('/users').end(function(err, res){ // assume this gets array of all users
  //     var num_user = res.body.length;
  //
  //     chai.request(server).post('/users').send({'username':'tester','age':24})
  //       .end(function(err, res){
  //         var num_user2 = res.body.length; // assuming response contains user array
  //         (num_user2 - num_user).should.equal(1);
  //         done();
  //       });
  //   });
  // });
});

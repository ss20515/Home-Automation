var mainApp = {};
var userdetials = {};
(function(){

	var firebase = app_fireBase;

    firebase.auth().onAuthStateChanged(function(user) {
        if (user) {
            // User is signed in.
            const uid = user.uid;
            userdetials.displayName = user.displayName;
            window.localStorage.setItem('status', 'Welcome '+userdetials.displayName+'! Your home is secure');
        }
        else{
            // redirect to login
            uid = null;
            window.location.replace("login.html");
        }
    });


   function logOut(){
   	    firebase.auth().signOut();
   }

   mainApp.logOut = logOut;
})()
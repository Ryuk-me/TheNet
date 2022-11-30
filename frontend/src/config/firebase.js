// Import the functions you need from the SDKs you need
import { initializeApp } from "firebase/app";
import { getAnalytics } from "firebase/analytics";
import { getAuth, GoogleAuthProvider } from "firebase/auth";
// TODO: Add SDKs for Firebase products that you want to use
// https://firebase.google.com/docs/web/setup#available-libraries

// Your web app's Firebase configuration
// For Firebase JS SDK v7.20.0 and later, measurementId is optional
const firebaseConfig = {
  apiKey: "AIzaSyCx9-dnw7GGNvHeysjzdkGdk8aIvhSVaQ0",
  authDomain: "the-net-e0edf.firebaseapp.com",
  databaseURL: "https://the-net-e0edf-default-rtdb.firebaseio.com",
  projectId: "the-net-e0edf",
  storageBucket: "the-net-e0edf.appspot.com",
  messagingSenderId: "605533050991",
  appId: "1:605533050991:web:f0a304844cc00d74b1559a",
  measurementId: "G-3CQCZ4LST2",
};

// Initialize Firebase
const app = initializeApp(firebaseConfig);
const analytics = getAnalytics(app);

export const auth = getAuth(app);
export const provider = new GoogleAuthProvider(app);

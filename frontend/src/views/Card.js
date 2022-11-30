import React, { useEffect } from "react";
import { Link } from "react-router-dom";
// import sections
import FormHint from "../components/elements/FormHint";
import FormLabel from "../components/elements/FormLabel";
import Input from "../components/elements/Input";
import Button from "../components/elements/Button";
import "../assets/scss/settings/sections/card.css";
import { auth, GoogleAuthProvider, provider } from "../config/firebase";
import { useAuthState } from "react-firebase-hooks/auth";
import { signInWithPopup } from "firebase/auth";
import Home from "./Home";

const Card = () => {
  const [user] = useAuthState(auth);

  // fetch("http://localhost:5050/api/v1/user", {
  //   method: "POST",
  //   headers: { "Content-Type": "application/json" },
  //   body: JSON.stringify({
  //     name: "X",
  //     firebase_id: "0987",
  //     email: "x@gmail.com",
  //   }),
  // }).then((data) => {
  //   console.log(data);
  // });
  fetch("http://localhost:5050/api/v1/user", {
    method: "POST",
    headers: { "Content-Type": "application/json" },
    body: JSON.stringify({
      name: "X",
      firebase_id: "0987",
      email: "x@gmail.com",
    }),
  }).then((data) => {
    console.log(data);
  });

  return (
    <>
      <div className="Card">
        <h1
          className="mt-0 mb-16 reveal-from-bottom center"
          data-reveal-delay="200"
        >
          The <span className="text-color-primary">NET</span>
        </h1>
        <div className="left">
          <div className="user">
            <center>
              <img
                src={user?.photoURL || ""}
                width="80"
                height="100"
                className="photo"
              ></img>
              <p className="username">{user?.displayName}</p>
            </center>
          </div>
          <div className="nav">
            <ul>
              <li>
                <Link to="/Home.js">Home</Link>
              </li>
              <li>
                <Link to="">Add Notes</Link>
              </li>
              <li>
                <a href="mailto:tanupamsaha26@gmail.com">Contact Us</a>
              </li>
            </ul>
          </div>
        </div>
        <div className="right">
          <input
            type="text"
            className="search"
            placeholder="Let's search your note?"
          />
          <i className="bx bx-search"></i>

          <div className="notes"></div>
        </div>
      </div>
    </>
  );
};

export default Card;

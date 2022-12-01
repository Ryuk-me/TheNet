import React, { useEffect, useState } from "react";
import { Link } from "react-router-dom";
import axios from "axios";
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
  const [message, setMessage] = useState("");
  const [updated, setUpdated] = useState("");
  const handlChange = (event) => {
    setMessage(event.target.value);
  };
  const [notes, fetchNotes] = useState([]);
  const fetchNotesOnPageLoad = () => {
    dataFetch();
  };
  const FileDownload = require("js-file-download");

  useEffect(() => {
    fetchNotesOnPageLoad();
  }, []);

  function dataFetch() {
    fetch("http://localhost:5050/api/v1/notes", {
      method: "GET",
      headers: {
        Authorization: "123",
      },
    })
      .then((data) => data.json())
      .then((data) => {
        fetchNotes(data.results);
      });
  }
  const handleKeyDown = (event) => {
    if (event.key === "Enter") {
      dataFetch();
    }
  };

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
              {/* <li>
                <Link to="">Add Notes</Link>
              </li> */}
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
            onKeyDown={handleKeyDown}
          />
          {/* <i className="bx bx-search"></i> */}

          <div className="notesSection">
            {notes.length > 0 && (
              <ul className="notesSection">
                {notes.map((post) => (
                  <li className="notesFetched" key={post.file_name}>
                    {post.file_name}
                    <Button tag="a" color="primary" wideMobile>
                      <a href={post.file_location} download={post.file_name}>
                        <button>Download</button>
                      </a>
                    </Button>
                  </li>
                ))}{" "}
              </ul>
            )}
          </div>
        </div>
      </div>
    </>
  );
};

export default Card;

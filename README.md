# README

This project is about test-driving a simple 2D game engine that can switch between different backend APIs (such as GTK, SDL, ...). I'm also creating a Pong game to help me design and test the engine.

The game engine implements an Entity-Component-Manager architecture.

You can add entities to the game, and these entities have components, each managed by component managers.

The different pieces of the project are:

- `Facineroso`: This layer creates an abstraction from the backend libraries.
- `Pichon`: This is the actual game engine.
- `Pong`: This is the classic Pong game.


# Predator-Prey Systems Project

**Author :** Remy XU


**Project Type :** Supervised group project of 4


## Overview

This project is part of our third-year computer science curriculum at Université Paris Cité. The goal is to simulate a realistic predator-prey system to observe trophic cascades and study the behaviors of different animal and plant species under various environmental conditions.

## Project Description

### Context

Our project builds upon an existing simulation to correct and enhance its features. The aim is to create a realistic predator-prey system to observe trophic cascades and understand ecosystem dynamics.

### Objectives

- Correct and improve existing functionalities.
- Implement new features such as mimicry and pack systems.

### Technologies

- **Unity3D**: Used for the entire simulation development.
- **Visual Studio**: Used for coding and debugging.
- **Discord**: For team communication and coordination.
- **Forge**: For project management and version control.
- **LucidChart**: For creating diagrams and documentation.
- **Tortoise SVN**: For version control and collaboration.

## Features

### Agent Addition

- Add agents during the simulation with adjustable parameters.
- Default values for agent statistics are provided but can be modified by the user.

### Pack System

- Agents of the same species can form packs.
- Packs hunt and move together, with an alpha leading the group.
- The alpha has priority access to resources and can be challenged by other pack members.

### Mimicry

- Agents can mimic the behavior of other agents if it improves their survival chances.
- Agents can copy actions such as eating, drinking, sleeping, and fleeing based on observed behaviors.

### Teleportation

- Teleport to any agent in the simulation by pressing the 'T' key.
- Cycle through agents based on their creation date.
- Teleport to specific species using the teleportation button.

### Agent Control

- Control an agent manually by selecting its point of view and enabling manual control.
- Perform actions such as moving, sprinting, attacking, eating, drinking, and sleeping.
- Manual actions can influence other agents through mimicry.

### Weather and Season System

- Dynamic weather system affecting the entire terrain.
- Seasonal changes with visual and behavioral impacts on agents.
- Temperature fluctuations based on weather and season.

### Agent Behavior Improvement

- Agents can now get unstuck from obstacles.
- Injured agents regenerate health over time.
- Fear system implemented where agents flee from predators.
- Swimming system with oxygen and fatigue mechanics.

### User Interface Improvements

- Default values for agent and terrain parameters.
- Options menu for graphics and controls.
- Enhanced statistics display for agents.
- Manual adjustment of agent health, endurance, hunger, thirst, and fear.

### Terrain Modification

- Reduced terrain relief to ensure full NavMesh coverage.
- Prevents agents from getting stuck and ensures smooth movement.

### Laboratory Enhancements

- Added new species with behavior trees, statistics, and prey lists.
- Increased diversity and realism of the simulation.

## Problems Encountered

- Numerous bugs and non-functional legacy features.
- Challenges in merging individual work and managing scene configurations.
- Performance issues with simulation speed and agent behaviors.

## Conclusion

This project provided a comprehensive experience in software development, team collaboration, and documentation. Future improvements could include:

- Cooperative behaviors among prey to avoid predators.
- Disease and injury systems.
- Migration based on seasonal changes.
- Addition of marine, flying, or scavenging species.
- Territory systems for packs.
- Global code optimization.

## Glossary

- **GameObject**: Entities instantiated in the scene to make scripts functional and connect different objects.
- **Unity Scene**: Contains objects of our simulation, used to create main menus, individual levels, etc.
- **Trophic Cascade**: Indirect effects of predators on lower trophic levels in an ecosystem.

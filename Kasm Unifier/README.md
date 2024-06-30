# Kasm Unifier
This work is based on the excellent work PluginGuru.com Unify (Shane)

The ulterior motive here is finding a good way to self maintain your 
own instrument presets in an easy-to-share patch format

A format that works across _all_ DAWs with the intention of seeding an 
open standard everyone can easily adopt and improve on without consequences

The actual goal is Web based MIDI players, in particular VR/AR can 
later be used to compose music, support remote live collaborative 
music production, things like that

[Kasm](https://github.com/kevleyski/kasm) is Kev's side project that generates
and tweaks instrument and effect patches by feeding back the mix bus into
a WebAssemply plugin. 
It's main use case is WebXR immersive AR, but if things can works identically
in Ableton Live, Cubase, Pro Tools, Logic, GarageBands, Bitwig etc through 
an open standards collaboration, then that'll be pretty neat

Note, as this is based entirely on the PluginGuru Unifier examples this also
uses the [JUCE framework](https://github.com/juce-framework/JUCE)
I've included a CMake file that will drop into that (e.g. examples)

With this I managed to get things to build/run and step debug with 
JetBrains CLion on macOS. The goal is to migrate things towards Rust 
which better enforces security with tighter/less buggy code
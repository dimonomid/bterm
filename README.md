
# Bot Terminal

Bot Terminal is a crossplatform utility that performs binary data exchange via serial port. It allows one to set up flexible rules about how to reply to different requests. So, it listens for data, parses it, and replies as necessary.

I developed this tool in order to reverse-engineer various binary protocols of car ECUs (Engine Control Unit). I connect some car diagnostic tool (tester) to the computer with Bot Terminal running, and it pretends to be an ECU. By replying different responses on the tester's requests, and by analyzing tester's behavior, I can make some assumptions about the protocol. That's easy.

I'm not sure whether it can be used for anything else. Anyway, it is published with the hope that it can.

A couple of useful links:

- [Overall doxygen-generated documentation](http://dfrank.bitbucket.org/bterm/x/html/)
- User's documentation:
    - [JavaScript host API](http://dfrank.bitbucket.org/bterm/x/html/js_api.html)
- Developer's documentation:
    - [BTCore: implementation overview](http://dfrank.bitbucket.org/bterm/x/html/btcore.html)


Here is an overview of the workflow:

- New raw data comes from the serial port
- Raw data is parsed into messages, by means of `BTCore::Codec`
- For each received message, the sequence of the user-defined handlers is executed. Each handler may:
    - Analyze input request message
    - Build and send response message (which is usually, again, encoded with `#BTCore::Codec`, but the handler is free to send raw data as well)
    - Stop further handlers execution (typically this is done when handler sends a response, but this is not mandatory)

Handlers are written in JavaScript. Typical handler may look as follows:

```javascript
(function(inputMsg){
    //-- inputMsg contains the received request data.
    //   at the very least, it contains "byteArr" property
    //   with actual received message.

    var inputArr = inputMsg.byteArr;
    var handled = false;
    var outputArr = null;

    //-- check if we should handle this request
    if (inputArr.getU08(0) === 0x07){
        //-- yes, so, build the response
        outputArr = factory.createByteArr();
        outputArr
            .putU08(0, 0xc7)
            .putU16(2, 0x1234)
            ;
        handled = true;

        //-- encode and send response via serial port
        io.writeEncoded(outputArr);
    };

    //-- if "handled" property in the returned object is true,
    //   the rest of handlers won't be executed
    return {
        handled: handled
    };
})
```

The code is self-explanatory: we perform some arbitrary checks on received message, and generate and send the response if necessary.

Why JavaScript?

- Well, the first and main reason is that Qt has built-in first-class support of JavaScript: [QJSEngine](http://doc.qt.io/qt-5/qjsengine.html). Implementing support of other scripting language to the same degree of interconnection with Qt's meta object system would take **a lot** more effort.
- Secondly, I know JavaScript very well and I even kind of like it. So, implementing handlers in JavaScript was a lot of fun.

You don't have to have deep understanding of JavaScript in order to use the Bot Terminal.

Just in case you're willing to actually learn JavaScript (for whatever reason), here's a couple of books that I personally recommend:

- [JavaScript: The Good Parts](http://www.amazon.com/JavaScript-Good-Parts-Douglas-Crockford/dp/0596517742) by Douglas Crockford. It focuses on a subset of JavaScript (a good subset), it teaches you very useful patterns, and it is very concise: lots of material in less than 200 pages. Great read.
- [JavaScript: The Definitive Guide](http://www.amazon.com/JavaScript-Definitive-Guide-Activate-Guides/dp/0596805527) by David Flanagan. It is much larger (1000+ pages), and it explains each and every detail of JavaScript. Great for getting deep understanding of the language.

But, again, if the only JavaScript application you have is to use Bot Terminal, then you probably have something better to do rather than spending your valuable time on diving that deeply into JavaScript. Just read my brief overview.

The graphics interface of the application looks like this:

![bterm_medium.png](https://bitbucket.org/repo/k69bGX/images/3758058215-bterm_medium.png)

The GUI is actually very flexible: main window contains an application log, and a number of dock widgets, which can be moved around, shown docked or undocked, or hidden. For example, there are a couple of other dock widgets that are not shown at the screenshot above: the project settings (title and codec selection), and codec settings (which, of course, depend on codec).

Check the doxygen-generated documentation (links are above) for details.



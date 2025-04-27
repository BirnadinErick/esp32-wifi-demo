Bun.serve({
    port:2003,
    hostname: "0.0.0.0",
    routes: {
        "/health": new Response("HEALTHY!"),
        "/save-data": {
            POST: async req => {
                const body = await req.text();
                console.log(body);
                return Response("1");
            }
        }
    }
});
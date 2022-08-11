function OnInit(id)
    print("[lua] main Oninit id: "..id)

    local ping1 = sunnet.NewService("ping")
    print("[lua] new service ping1  "..ping1)

    local ping2 = sunnet.NewService("ping")
    print("[lua] new service ping2  "..ping2)

    local pong = sunnet.NewService("pong")
    print("[lua] new service pong  "..pong)

    sunnet.Send(ping1, pong, "start")
    sunnet.Send(ping2, pong, "start")
end    
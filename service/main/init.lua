function OnInit(id)
    print("[lua] main Oninit id: "..id)

    local ping1 = sunnet.NewService("ping")
    print("[lua] new service ping1  "..ping1)

    local ping2 = sunnet.NewService("ping")
    print("[lua] new service ping2  "..ping2)

    local ping3 = sunnet.NewService("ping")
    print("[lua] new service ping3  "..ping3)
end    
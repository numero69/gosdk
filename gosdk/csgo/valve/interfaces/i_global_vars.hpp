#pragma once

namespace CS::Interfaces {
  class IGlobalVars {
  public:
    float RealTime;
    int FrameCount;
    float AbsoluteFrameTime;
    float AbsoluteFrameTimeStdDev;
    float CurrentTime;
    float FrameTime;
    int MaxClients;
    int TickCount;
    float IntervalPerTick;
    float InterpolationAmount;
    std::int32_t SimulatedTicksPerFrame;
    std::int32_t NetworkProtocol;
    void * SaveData;
    bool Client;
    bool RemoteClient;
  };
} // namespace CS::Interfaces
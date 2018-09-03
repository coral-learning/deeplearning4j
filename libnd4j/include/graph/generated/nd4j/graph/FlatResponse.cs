// <auto-generated>
//  automatically generated by the FlatBuffers compiler, do not modify
// </auto-generated>

namespace nd4j.graph
{

using global::System;
using global::FlatBuffers;

public struct FlatResponse : IFlatbufferObject
{
  private Table __p;
  public ByteBuffer ByteBuffer { get { return __p.bb; } }
  public static FlatResponse GetRootAsFlatResponse(ByteBuffer _bb) { return GetRootAsFlatResponse(_bb, new FlatResponse()); }
  public static FlatResponse GetRootAsFlatResponse(ByteBuffer _bb, FlatResponse obj) { return (obj.__assign(_bb.GetInt(_bb.Position) + _bb.Position, _bb)); }
  public void __init(int _i, ByteBuffer _bb) { __p.bb_pos = _i; __p.bb = _bb; }
  public FlatResponse __assign(int _i, ByteBuffer _bb) { __init(_i, _bb); return this; }

  public int Status { get { int o = __p.__offset(4); return o != 0 ? __p.bb.GetInt(o + __p.bb_pos) : (int)0; } }

  public static Offset<FlatResponse> CreateFlatResponse(FlatBufferBuilder builder,
      int status = 0) {
    builder.StartObject(1);
    FlatResponse.AddStatus(builder, status);
    return FlatResponse.EndFlatResponse(builder);
  }

  public static void StartFlatResponse(FlatBufferBuilder builder) { builder.StartObject(1); }
  public static void AddStatus(FlatBufferBuilder builder, int status) { builder.AddInt(0, status, 0); }
  public static Offset<FlatResponse> EndFlatResponse(FlatBufferBuilder builder) {
    int o = builder.EndObject();
    return new Offset<FlatResponse>(o);
  }
};


}
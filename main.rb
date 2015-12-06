
public

def start
  @margin = 10

  @height = 580.0
  @growth = -1
  @fact = 3

  @segments = 12
end

def update
  @height += @growth * @fact

  if @growth < 0 && @height <= 200
    @growth = 1
  elsif @growth > 0 && @height >= 580
    @growth = -1
  end
end

def draw
  @segment_size = @height/@segments

  (@segments + 1).times do |i|
    line(@margin, @margin + i* @segment_size, @margin + i * @segment_size, @margin + @height)
  end
end

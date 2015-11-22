
clear()

margin = 10

height = 500.0
segments = 8
segment_size = height/segments

(segments + 1).times do |i|
  line(margin, margin + i* segment_size, margin + i * segment_size, margin + height)
end
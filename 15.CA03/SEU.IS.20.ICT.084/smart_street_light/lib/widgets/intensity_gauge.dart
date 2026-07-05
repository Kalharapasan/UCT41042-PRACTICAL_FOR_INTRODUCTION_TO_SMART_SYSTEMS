import 'package:flutter/material.dart';
import 'dart:math' as math;

class IntensityGauge extends StatelessWidget {
  final int intensity;

  const IntensityGauge({super.key, required this.intensity});

  Color get _arcColor {
    if (intensity > 70) return const Color(0xFF00E676);
    if (intensity >= 30) return const Color(0xFF40C4FF);
    if (intensity >= 15) return const Color(0xFFFF1744);
    return const Color(0xFFFF6D00);
  }

  @override
  Widget build(BuildContext context) {
    return Column(
      mainAxisSize: MainAxisSize.min,
      children: [
        SizedBox(
          width: 140,
          height: 80,
          child: CustomPaint(
            painter: _GaugePainter(
              value: intensity / 100.0,
              color: _arcColor,
            ),
          ),
        ),
        const SizedBox(height: 4),
        RichText(
          textAlign: TextAlign.center,
          text: TextSpan(
            children: [
              TextSpan(
                text: '$intensity',
                style: TextStyle(
                  color: _arcColor,
                  fontSize: 36,
                  fontWeight: FontWeight.w800,
                  height: 1,
                ),
              ),
              TextSpan(
                text: '%',
                style: TextStyle(
                  color: _arcColor.withOpacity(0.7),
                  fontSize: 18,
                  fontWeight: FontWeight.w500,
                ),
              ),
            ],
          ),
        ),
        const SizedBox(height: 4),
        Text(
          'LIGHT INTENSITY',
          style: TextStyle(
            color: Colors.white.withOpacity(0.4),
            fontSize: 10,
            letterSpacing: 2.0,
            fontWeight: FontWeight.w600,
          ),
        ),
      ],
    );
  }
}

class _GaugePainter extends CustomPainter {
  final double value;
  final Color color;

  _GaugePainter({required this.value, required this.color});

  @override
  void paint(Canvas canvas, Size size) {
    final cx = size.width / 2;
    final cy = size.height;
    final radius = size.width / 2 - 8;

    // Background arc
    final bgPaint = Paint()
      ..color = Colors.white.withOpacity(0.08)
      ..style = PaintingStyle.stroke
      ..strokeWidth = 10
      ..strokeCap = StrokeCap.round;

    canvas.drawArc(
      Rect.fromCircle(center: Offset(cx, cy), radius: radius),
      math.pi,
      math.pi,
      false,
      bgPaint,
    );

    // Value arc
    final fgPaint = Paint()
      ..color = color
      ..style = PaintingStyle.stroke
      ..strokeWidth = 10
      ..strokeCap = StrokeCap.round;

    canvas.drawArc(
      Rect.fromCircle(center: Offset(cx, cy), radius: radius),
      math.pi,
      math.pi * value,
      false,
      fgPaint,
    );

    // Glow
    final glowPaint = Paint()
      ..color = color.withOpacity(0.25)
      ..style = PaintingStyle.stroke
      ..strokeWidth = 18
      ..strokeCap = StrokeCap.round
      ..maskFilter = const MaskFilter.blur(BlurStyle.normal, 6);

    canvas.drawArc(
      Rect.fromCircle(center: Offset(cx, cy), radius: radius),
      math.pi,
      math.pi * value,
      false,
      glowPaint,
    );
  }

  @override
  bool shouldRepaint(_GaugePainter old) =>
      old.value != value || old.color != color;
}

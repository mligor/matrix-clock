import { Component } from '@angular/core';
import { BreakpointObserver, Breakpoints } from '@angular/cdk/layout';
import { Observable } from 'rxjs';
import { map } from 'rxjs/operators';

@Component({
	selector: 'app-matrix-clock-nav',
	templateUrl: './matrix-clock-nav.component.html',
	styleUrls: ['./matrix-clock-nav.component.scss'],
})
export class MatrixClockNavComponent {

	isHandset$: Observable<boolean> = this.breakpointObserver.observe(Breakpoints.Handset)
		.pipe(
			map(result => result.matches)
		);

	constructor(private breakpointObserver: BreakpointObserver) { }

}
